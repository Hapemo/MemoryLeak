#include "Input.h"
#include "pch.h"

std::array<bool, 324> Input::prev_key_states;
int Input::starting_index{ 32 };
int Input::total_mouse_key{ 8 };
int Input::max_keyboard_index{ 348 };
GLFWwindow* Input::window;
GLFWcursor* Input::cursor;

void Input::init(GLFWwindow* _window) {
  window = _window;

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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

Math::Vec2 Input::CursorPos() {
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return Math::Vec2{ static_cast<float>(xpos), static_cast<float>(ypos) };
}


