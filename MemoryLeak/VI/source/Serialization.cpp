/*!*****************************************************************************
\file Serialization.cpp
\author Huang Wei Jhin, Chen Jia Wenyy
\par DP email: h.weijhin@digipen.edu, jiawenny@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a Serialization system that saves and load
-Entities and its Components
-Dialogs
*******************************************************************************/
#include <Serialization.h>
#include <ECSManager.h>
#include <vec2.h>


using namespace rapidjson;
/*!*****************************************************************************
\brief
	Creats a vec2 using rapidjson value
\param
	vecIn rapidjason vetor 2 value

\return
None.
*******************************************************************************/
Math::Vec2 GetVec2(Value& vecIn)
{
	Math::Vec2 vecOut;
	vecOut.x = vecIn["X"].GetFloat();
	vecOut.y = vecIn["Y"].GetFloat();
	return vecOut;
}

/*!*****************************************************************************
\brief
	Loads the scene into ECS

\return
None.
*******************************************************************************/
void SerializationManager::LoadScene(std::string _filename)
{
	//"../resources/Scene/SceneJ.json"
	std::string path = "../resources/Scene/" + _filename + ".json";
	std::ifstream ifs(path);
	//std::ifstream ifs(filename);
	if (!ifs.good())
	{
		LOG_ERROR("Can't open json file! : " + path);
		return;
	}
	else
		LOG_ERROR("Opening Scene: " + path);
	std::stringstream contents;
	contents << ifs.rdbuf();
	Document doc;
	doc.Parse(contents.str().c_str());

	//std::cout << contents.str() << '\n';

	int i = 0;
	for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
	{
		
		Entity e{ ECS::CreateEntity() };
		Value entity(kObjectType);
		std::string str("Entity" + std::to_string(i));
		Value index(str.c_str(), (SizeType)str.size(), doc.GetAllocator());
		if (!doc.HasMember(index))
			std::cout << "error   "<<i;
		entity = doc[index];
	
		if (entity.HasMember("General"))
		{
			std::string name = entity["General"]["name"].GetString();
			bool isActive = entity["General"]["isActive"].GetBool();
			int tag = entity["General"]["tag"].GetInt();
			int subtag = entity["General"]["subtag"].GetInt();
			e.AddComponent<General>(General{ name, (TAG)tag ,(SUBTAG)subtag, isActive });
		}
		if (entity.HasMember("Lifespan"))
		{
			float lifetime = entity["Lifespan"]["lifetime"].GetFloat();
			float limit = entity["Lifespan"]["limit"].GetFloat();
			e.AddComponent<Lifespan>({ lifetime, limit });
		}
		if (entity.HasMember("Transform"))
		{
			Math::Vec2 s, t;
			float r;
			s.x = entity["Transform"]["scale"]["X"].GetFloat();
			s.y = entity["Transform"]["scale"]["Y"].GetFloat();
			r = (float)entity["Transform"]["rotation"].GetFloat();
			t.x = entity["Transform"]["translation"]["X"].GetFloat();
			t.y = entity["Transform"]["translation"]["Y"].GetFloat();
		
			e.AddComponent<Transform>({ s, r, t }); 
		}
		if (entity.HasMember("Sprite"))
		{
			Color c;
			c.r = (GLubyte)entity["Sprite"]["color"]["r"].GetInt();
			c.g = (GLubyte)entity["Sprite"]["color"]["g"].GetInt();
			c.b = (GLubyte)entity["Sprite"]["color"]["b"].GetInt();
			c.a = (GLubyte)entity["Sprite"]["color"]["a"].GetInt();
			SPRITE s = (SPRITE)entity["Sprite"]["sprite"].GetInt();
			GLuint t = (GLuint)entity["Sprite"]["texture"].GetInt();
			int l = entity["Sprite"]["layer"].GetInt();
			e.AddComponent<Sprite>({ c, s, t ,l});
		}
		if (entity.HasMember("Animation"))
		{
			std::vector<GLuint> images;
			Value a(kObjectType);
			a = entity["Animation"]["images"].GetArray();
			for (int j = 0; j < (int)a.Size(); ++j)
			{
				images.push_back((GLuint)a[j].GetInt());
			}
			float timePerImage = entity["Animation"]["timePerImage"].GetFloat();
			float timeToImageSwap = entity["Animation"]["timeToImageSwap"].GetFloat();
			int currentImageIndex = entity["Animation"]["currentImageIndex"].GetInt();
			e.AddComponent<Animation>({ images , timePerImage , timeToImageSwap , currentImageIndex });
		} 
		if (entity.HasMember("SheetAnimation"))
		{
			short frameCount = (short)entity["SheetAnimation"]["frameCount"].GetInt();
			short currentImageIndex = (short)entity["SheetAnimation"]["currFrameIndex"].GetInt();
			float timePerImage = entity["SheetAnimation"]["timePerFrame"].GetFloat();
			float timeToImageSwap = entity["SheetAnimation"]["timeToFrameSwap"].GetFloat();
			e.AddComponent<SheetAnimation>({ frameCount , currentImageIndex , timePerImage , timeToImageSwap });
		}
		if (entity.HasMember("Physics2D"))
		{
			float mass = entity["Physics2D"]["mass"].GetFloat();
			float	speed = entity["Physics2D"]["speed"].GetFloat();
			float	moveDirection = entity["Physics2D"]["moveDirection"].GetFloat();
			bool gravityEnabled = false;
			if(entity["Physics2D"].HasMember("gravityEnabled"))
				gravityEnabled = entity["Physics2D"]["gravityEnabled"].GetBool();
			bool renderFlag = entity["Physics2D"]["renderFlag"].GetBool();

			e.AddComponent<Physics2D>({ gravityEnabled, mass, speed, moveDirection, Math::Vec2{0, 0}, Math::Vec2{0, 0}, renderFlag });
			//physics2DManager->AddPhysicsComponent(e, mass, speed, moveDirection, renderFlag);
		}
		if (entity.HasMember("RectCollider"))
		{
			Math::Vec2 centerOffset = GetVec2(entity["RectCollider"]["centerOffset"]);
			Math::Vec2	scaleOffset = GetVec2(entity["RectCollider"]["scaleOffset"]);
			bool renderFlag = entity["RectCollider"]["renderFlag"].GetBool();
			e.AddComponent<RectCollider>({ centerOffset , scaleOffset , renderFlag });
		}
		if (entity.HasMember("CircleCollider"))
		{
			Math::Vec2 centerOffset = GetVec2(entity["CircleCollider"]["centerOffset"]);
			float scaleOffset = entity["CircleCollider"]["scaleOffset"].GetFloat();
			bool renderFlag = entity["CircleCollider"]["renderFlag"].GetBool();
			e.AddComponent<CircleCollider>({ centerOffset , scaleOffset , renderFlag });
		}
		if (entity.HasMember("Edge2DCollider"))
		{
			Math::Vec2 p0Offset = GetVec2(entity["Edge2DCollider"]["p0Offset"]);
			float rotationOffset = entity["Edge2DCollider"]["rotationOffset"].GetFloat();
			float scaleOffset = entity["Edge2DCollider"]["scaleOffset"].GetFloat();
			bool renderFlag = entity["Edge2DCollider"]["renderFlag"].GetBool();

			e.AddComponent<Edge2DCollider>({ p0Offset ,rotationOffset, scaleOffset , renderFlag });
		}
		if (entity.HasMember("Point2DCollider"))
		{
			Math::Vec2 centerOffset = GetVec2(entity["Point2DCollider"]["centerOffset"]);
			bool renderFlag = entity["Point2DCollider"]["renderFlag"].GetBool();
			e.AddComponent<Point2DCollider>({ centerOffset ,renderFlag });
		}
		if (entity.HasMember("Audio"))
		{
			Sound sound;
			sound.path = entity["Audio"]["path"].GetString();
			sound.volume  = entity["Audio"]["volume"].GetFloat();
			sound.volumeMod = entity["Audio"]["volumeMod"].GetFloat();
			sound.pitch = entity["Audio"]["pitch"].GetFloat();
			sound.isPaused = entity["Audio"]["isPaused"].GetBool();
			sound.isMute = entity["Audio"]["isMute"].GetBool();
			sound.isLoop = entity["Audio"]["isLoop"].GetBool();
			sound.isRandPitch = entity["Audio"]["isRandPitch"].GetBool();

			bool isSpacial = entity["Audio"]["isSpacial"].GetBool();
			e.AddComponent<Audio>({ sound , isSpacial});
		}
		mEntities.insert(e);
		i++;
	}
}

/*!*****************************************************************************
\brief
	Adds a vector 2 to a rapid jason dom tree

\return
None.
*******************************************************************************/
void addVectorMember(Document& scene, Value& parent, const char* name, Math::Vec2 data)
{
	Value child(kObjectType);
	child.AddMember(StringRef("X"), data.x, scene.GetAllocator());
	child.AddMember(StringRef("Y"), data.y, scene.GetAllocator());
	parent.AddMember(StringRef(name), child, scene.GetAllocator());
}

/*!*****************************************************************************
\brief
	Adds a vector to a rapid jason dom tree as a array
\param scene
	rapid jason document to add to 
\param parent
	parent onject to add to 
\param name
	name of child to add to parant object
\prama data
	data to be added to the child objects
		
\return
None.
*******************************************************************************/
template<typename T>
void addVectorArrayMember(Document& scene, Value& parent, const char* name, std::vector <T> data)
{
	Value child(kObjectType);
	child.SetArray();
	for (size_t i = 0; i < data.size(); ++i)
	{
		child.PushBack(data.at(i), scene.GetAllocator());
	}
	parent.AddMember(StringRef(name), child, scene.GetAllocator());
}

/*!*****************************************************************************
\brief
	Adds a vector to a rapid jason dom tree as individual child objects
\param scene
	rapid jason document to add to
\param parent
	parent onject to add to
\param name
	name of child to add to parant object
\prama data
	data to be added to the child objects
\return
None.
*******************************************************************************/
template<typename T>
void addVectorsMember(Document& scene, Value& parent, const char* name, std::vector <T> data)
{
	Value child(kObjectType);
	for (size_t i = 0; i < data.size(); ++i)
	{
		std::string num = std::to_string(i);
		Value number(num.c_str(), (SizeType)num.size(), scene.GetAllocator());
		child.AddMember(number, data[i], scene.GetAllocator());
	}
	parent.AddMember(StringRef(name), child, scene.GetAllocator());
}
/*!*****************************************************************************
\brief
	Saves the data in the ECS system to a json file

\return
None.
*******************************************************************************/
void SerializationManager::SaveScene(std::string _filename)
{
	Document scene;
	auto& allocator = scene.GetAllocator();
	scene.SetObject();
	
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	int counter = 0;
	
	for (const Entity& e : mEntities)
	{
		Value entity(kObjectType);
		if (e.HasComponent<General>())
		{
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("name"), StringRef(e.GetComponent<General>().name.c_str()), allocator);
			tmp.AddMember(StringRef("tag"), (int)e.GetComponent<General>().tag, allocator);
			tmp.AddMember(StringRef("subtag"), (int)e.GetComponent<General>().subtag, allocator);
			tmp.AddMember(StringRef("isActive"), e.GetComponent<General>().isActive, allocator);
			entity.AddMember(StringRef("General"), tmp, allocator);
		}
		if (e.HasComponent<Transform>())
		{
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "scale", e.GetComponent<Transform>().scale);
			tmp.AddMember(StringRef("rotation"), e.GetComponent<Transform>().rotation, allocator);
			addVectorMember(scene, tmp, "translation", e.GetComponent<Transform>().translation);
			entity.AddMember(StringRef("Transform"), tmp, allocator);
		}
		if (e.HasComponent<Sprite>())
		{
			Value tmp(kObjectType);
			Value tmpc(kObjectType);
			tmpc.AddMember(StringRef("r"), e.GetComponent<Sprite>().color.r, allocator);
			tmpc.AddMember(StringRef("g"), e.GetComponent<Sprite>().color.g, allocator);
			tmpc.AddMember(StringRef("b"), e.GetComponent<Sprite>().color.b, allocator);
			tmpc.AddMember(StringRef("a"), e.GetComponent<Sprite>().color.a, allocator);
			tmp.AddMember(StringRef("color"), tmpc, allocator);
			tmp.AddMember(StringRef("sprite"), (int)e.GetComponent<Sprite>().sprite, allocator);
			tmp.AddMember(StringRef("texture"), (int)e.GetComponent<Sprite>().texture, allocator);
			tmp.AddMember(StringRef("layer"), e.GetComponent<Sprite>().layer, allocator);
			entity.AddMember(StringRef("Sprite"), tmp, allocator);
		}
		if (e.HasComponent<Animation>())
		{
			Value tmp(kObjectType);
			addVectorArrayMember(scene, tmp, "images", e.GetComponent<Animation>().images);
			tmp.AddMember(StringRef("timePerImage"), e.GetComponent<Animation>().timePerImage, allocator);
			tmp.AddMember(StringRef("timeToImageSwap"), e.GetComponent<Animation>().timeToImageSwap, allocator);
			tmp.AddMember(StringRef("currentImageIndex"), e.GetComponent<Animation>().currentImageIndex, allocator);
			entity.AddMember(StringRef("Animation"), tmp, allocator);
		}
		if (e.HasComponent<SheetAnimation>()) 
		{
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("frameCount"), e.GetComponent<SheetAnimation>().frameCount, allocator);
			tmp.AddMember(StringRef("currFrameIndex"), e.GetComponent<SheetAnimation>().currFrameIndex, allocator);
			tmp.AddMember(StringRef("timePerFrame"), e.GetComponent<SheetAnimation>().timePerFrame, allocator);
			tmp.AddMember(StringRef("timeToFrameSwap"), e.GetComponent<SheetAnimation>().timeToFrameSwap, allocator);
			entity.AddMember(StringRef("SheetAnimation"), tmp, allocator);
		}
		if (e.HasComponent<Physics2D>())
		{
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("mass"), e.GetComponent<Physics2D>().mass, allocator);
			tmp.AddMember(StringRef("speed"), e.GetComponent<Physics2D>().speed, allocator);
			tmp.AddMember(StringRef("moveDirection"), e.GetComponent<Physics2D>().moveDirection, allocator);
			addVectorMember(scene, tmp, "forces",  e.GetComponent<Physics2D>().forces);
			addVectorMember(scene, tmp, "velocity", e.GetComponent<Physics2D>().velocity);
			tmp.AddMember(StringRef("gravityEnabled"), e.GetComponent<Physics2D>().gravityEnabled, allocator);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<Physics2D>().renderFlag, allocator);
			entity.AddMember(StringRef("Physics2D"), tmp, allocator);
		}
		if (e.HasComponent<RectCollider>())
		{
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset",e.GetComponent<RectCollider>().centerOffset);
			addVectorMember(scene, tmp, "scaleOffset", e.GetComponent<RectCollider>().scaleOffset);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<RectCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("RectCollider"), tmp, allocator);
		}
		if (e.HasComponent<CircleCollider>())
		{
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset",e.GetComponent<CircleCollider>().centerOffset);
			tmp.AddMember(StringRef("scaleOffset"), e.GetComponent<CircleCollider>().scaleOffset, allocator);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<CircleCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("CircleCollider"), tmp, allocator);
		}
		if (e.HasComponent<Edge2DCollider>())
		{
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "p0Offset", e.GetComponent<Edge2DCollider>().p0Offset);
			tmp.AddMember(StringRef("rotationOffset"), e.GetComponent<Edge2DCollider>().rotationOffset, allocator);
			tmp.AddMember(StringRef("scaleOffset"), e.GetComponent<Edge2DCollider>().scaleOffset, allocator);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<Edge2DCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("Edge2DCollider"), tmp, allocator);
		}
		if (e.HasComponent<Point2DCollider>())
		{
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset", e.GetComponent<Point2DCollider>().centerOffset);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<Point2DCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("Point2DCollider"), tmp, allocator);
		}
		if (e.HasComponent<Audio>())
		{
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("path"), StringRef(e.GetComponent<Audio>().sound.path.c_str()), allocator);
			tmp.AddMember(StringRef("volume"), e.GetComponent<Audio>().sound.volume, allocator);
			tmp.AddMember(StringRef("volumeMod"), e.GetComponent<Audio>().sound.volumeMod, allocator);
			tmp.AddMember(StringRef("pitch"), e.GetComponent<Audio>().sound.pitch, allocator);
			tmp.AddMember(StringRef("isPaused"), e.GetComponent<Audio>().sound.isPaused, allocator);
			tmp.AddMember(StringRef("isMute"), e.GetComponent<Audio>().sound.isMute, allocator);
			tmp.AddMember(StringRef("isLoop"), e.GetComponent<Audio>().sound.isLoop, allocator);
			tmp.AddMember(StringRef("isRandPitch"), e.GetComponent<Audio>().sound.isRandPitch, allocator);
			tmp.AddMember(StringRef("isSpacial"), e.GetComponent<Audio>().isSpacial, allocator);
			entity.AddMember(StringRef("Audio"), tmp, allocator);
		}
		std::string s("Entity" + std::to_string(counter));
		Value index(s.c_str(), (SizeType)s.size(), allocator);
		scene.AddMember(index, entity, allocator);
		counter++;
	} 

	scene.Accept(writer);
	std::string jsonf(buffer.GetString(), buffer.GetSize());
	std::string path = "../resources/Scene/" + _filename + ".json";
	std::ofstream ofs(path);
	ofs << jsonf;
	if (!ofs.good() )
	{
		LOG_ERROR("Unable to save scene to: " + path);
	}
	else
		LOG_ERROR("Saved Scene: " + path);
}

/*!*****************************************************************************
\brief
	Loads the dialogs from a json file to the dialog manager

\return
None.
*******************************************************************************/
void SerializationManager::LoadDialogs()
{
	std::ifstream ifs("../resources/Dialogs/Dialog1.json");
	if (!ifs.good()) LOG_ERROR("Can't open json file!");
	LOG_INFO("Opening dialog json file!");

	std::stringstream contents;
	contents << ifs.rdbuf();
	Document doc;
	doc.Parse(contents.str().c_str());

	//std::cout << "contents.str() " << contents.str() << '\n';

	Dialog dialog;
	Value dialogObj(kObjectType);
	dialogObj = doc.GetArray();
	for (rapidjson::SizeType index = 0; index < dialogObj.Size(); ++index) {
		dialog.id = dialogObj[index]["Dialogue ID"].GetInt();
		dialog.text = dialogObj[index]["Dialogue Text"].GetString();
		//std::cout << "dialog.text " << dialog.text << '\n';
		dialog.speaker = dialogObj[index]["Speaker"].GetInt();
		dialog.next = dialogObj[index]["Next Dialogue"].GetInt();
		dialog.next2 = dialogObj[index]["Next Dialogue(2)"].GetInt();
		dialogManager->LoadDialog(dialog);
	}
}
/*!*****************************************************************************
\brief
	Saves the data in the dialog manager to a json file

\return
None.
*******************************************************************************/
void SerializationManager::SaveDialogs()
{
	/*
	LOG_INFO("saving dialogs");
	Document dialog;
	auto& allocator = dialog.GetAllocator();
	dialog.SetObject();

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	int counter = 0;

	for (const Dialog d : DialogManager::mDialogs)
	{
		Value entity(kObjectType);
		if (e.HasComponent<General>())
		{
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("name"), StringRef(e.GetComponent<General>().name.c_str()), allocator);
			tmp.AddMember(StringRef("tag"), (int)e.GetComponent<General>().tag, allocator);
			tmp.AddMember(StringRef("subtag"), (int)e.GetComponent<General>().subtag, allocator);
			tmp.AddMember(StringRef("isActive"), e.GetComponent<General>().isActive, allocator);
			entity.AddMember(StringRef("General"), tmp, allocator);
		}
	}

	scene.Accept(writer);
	std::string jsonf(buffer.GetString(), buffer.GetSize());
	std::ofstream ofs("../resources/Scene/SceneJ.json");
	ofs << jsonf;
	if (!ofs.good())
	{
		LOG_ERROR("json errorrr");
	}
	*/
}