#include "Input.h"
#include "pch.h"
#include "Application.h"

std::array<bool, 324> Input::prev_key_states;
int Input::starting_index{ 32 };
int Input::total_mouse_key{ 8 };
int Input::max_keyboard_index{ 348 };
GLFWwindow* Input::window;
GLFWcursor* Input::cursor;

void Input::init() {
  window = Application::getWindow();


  // Initialise all the callbacks for input
  // glfwSetKeyCallback(Application::getWindow(), key_cb);
  //glfwSetMouseButtonCallback(Application::getWindow(), mousebutton_cb);
  //glfwSetCursorPosCallback(Application::getWindow(), mousepos_cb);
  glfwSetScrollCallback(Application::getWindow(), mousescroll_cb);

  // this is the default setting ...
  glfwSetInputMode(Application::getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
 }

/*  _________________________________________________________________________*/
/*! key_cb

@param GLFWwindow*
Handle to window that is receiving event

@param int
the keyboard key that was pressed or released

@parm int
Platform-specific scancode of the key

@parm int
GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
action will be GLFW_KEY_UNKNOWN if GLFW lacks a key token for it,
for example E-mail and Play keys.

@parm int
bit-field describing which modifier keys (shift, alt, control)
were held down

@return none

This function is called when keyboard buttons are pressed.
When the ESC key is pressed, the close flag of the window is set.
*/
void Input::key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod) {
  std::cout << action << '\n';
  if (GLFW_PRESS == action) {
#ifdef _DEBUG
    std::cout << "Key pressed" << std::endl;
#endif
  }
  else if (GLFW_REPEAT == action) {
#ifdef _DEBUG
    std::cout << "Key repeatedly pressed" << std::endl;
#endif
  }
  else if (GLFW_RELEASE == action) {
#ifdef _DEBUG
    std::cout << "Key released" << std::endl;
#endif
  }

  if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
    glfwSetWindowShouldClose(pwin, GLFW_TRUE);
  }
}

/*  _________________________________________________________________________*/
/*! mousebutton_cb

@param GLFWwindow*
Handle to window that is receiving event

@param int
the mouse button that was pressed or released
GLFW_MOUSE_BUTTON_LEFT and GLFW_MOUSE_BUTTON_RIGHT specifying left and right
mouse buttons are most useful

@parm int
action is either GLFW_PRESS or GLFW_RELEASE

@parm int
bit-field describing which modifier keys (shift, alt, control)
were held down

@return none

This function is called when mouse buttons are pressed.
*/
void Input::mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod) {
  switch (button) {
  case GLFW_MOUSE_BUTTON_LEFT:
#ifdef _DEBUG
    std::cout << "Left mouse button ";
#endif
    break;
  case GLFW_MOUSE_BUTTON_RIGHT:
#ifdef _DEBUG
    std::cout << "Right mouse button ";
#endif
    break;
  }
  switch (action) {
  case GLFW_PRESS:
#ifdef _DEBUG
    std::cout << "pressed!!!" << std::endl;
#endif
    break;
  case GLFW_RELEASE:
#ifdef _DEBUG
    std::cout << "released!!!" << std::endl;
#endif
    break;
  }
}

/*  _________________________________________________________________________*/
/*! mousepos_cb

@param GLFWwindow*
Handle to window that is receiving event

@param double
new cursor x-coordinate, relative to the left edge of the client area

@param double
new cursor y-coordinate, relative to the top edge of the client area

@return none

This functions receives the cursor position, measured in screen coordinates but
relative to the top-left corner of the window client area.
*/
void Input::mousepos_cb(GLFWwindow* pwin, double xpos, double ypos) {
#ifdef _DEBUG
  std::cout << "Mouse cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
#endif
}

/*  _________________________________________________________________________*/
/*! mousescroll_cb

@param GLFWwindow*
Handle to window that is receiving event

@param double
Scroll offset along X-axis

@param double
Scroll offset along Y-axis

@return none

This function is called when the user scrolls, whether with a mouse wheel or
touchpad gesture. Although the function receives 2D scroll offsets, a simple
mouse scroll wheel, being vertical, provides offsets only along the Y-axis.
*/
void Input::mousescroll_cb(GLFWwindow* pwin, double xoffset, double yoffset) {
#ifdef _DEBUG
  std::cout << "Mouse scroll wheel offset: ("
    << xoffset << ", " << yoffset << ")" << std::endl;
#endif
}


bool Input::CheckKey(STATE state, KEY key) {
  int curr_state{};
  if ((int)key > max_keyboard_index)
    curr_state = glfwGetMouseButton(window, (int)key - max_keyboard_index - 1);
  else 
    curr_state = glfwGetKey(window, (int)key);

  switch (curr_state) {
  case 0: // Curr not pressed
    
    switch (prev_key_states[(int)key - starting_index]) {
    case 0: // Prev not pressed
      return state == NOTPRESS;
      break;
    case 1: // Prev pressed
      return state == RELEASE;
      break;
    }
    break;
  
  case 1: // Curr pressed
  
    switch (prev_key_states[(int)key - starting_index]) {
    case 0: // Prev not pressed
      return state == PRESS;
      break;
    case 1: // Prev pressed
      return state == HOLD;
      break;
    }

   default:
    std::cout << "Invalid current keyId: " + std::to_string((int)key) + " | with current state: " + std::to_string(glfwGetKey(window, (int)key)) << '\n';
    assert(0 && "Invalid current key pressed");

  }
  return 0;
}

void Input::updatePrevKeyStates() {
  for (int i = 0; i < static_cast<int>(sizeof(prev_key_states)) - total_mouse_key; ++i)
    prev_key_states[i] = (bool)glfwGetKey(window, starting_index + i);
  for (int i = static_cast<int>(sizeof(prev_key_states)) - total_mouse_key + 1, j = 0; i < static_cast<int>(sizeof(prev_key_states)); ++i, ++j) {
    prev_key_states[i] = (bool)glfwGetMouseButton(window, j);
  }
}

double Input::cursorPosX() {
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return xpos;
}

double Input::cursorPosY() {
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return ypos;
}


