/*!*****************************************************************************
\file Serialization.cpp
\author Huang Wei Jhin, Chen Jia Wen
\par DP email: h.weijhin@digipen.edu, c.jiawen@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a Serialization system that saves and load
-Entities and its Components
-Dialogs
TODO: take note not to change the component registration order. It will break prefab
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
		LOG_INFO("Opening Scene: " + path);
	ECS::DestroyAllEntities();
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
			if (tag == (int)TAG::PLAYER)
				e.AddComponent(PlayerTmp{ 0 });
		}
		if (entity.HasMember("Lifespan"))
		{
			float lifetime = entity["Lifespan"]["lifetime"].GetFloat();
			float limit = entity["Lifespan"]["limit"].GetFloat();
			e.AddComponent<Lifespan>({ lifetime, limit });
		}
		if (entity.HasMember("Transform"))
		{
			Math::Vec2 s = GetVec2(entity["Transform"]["scale"]);
			float r = (float)entity["Transform"]["rotation"].GetFloat();
			Math::Vec2 t = GetVec2(entity["Transform"]["translation"]);
		
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
			GLuint t = (GLuint)spriteManager->GetTextureID(entity["Sprite"]["texture"].GetString());
			//GLuint t = (GLuint)entity["Sprite"]["texture"].GetInt();
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
<<<<<<< Updated upstream
				GLuint tex = spriteManager->GetTextureID(a[j].GetString());
				images.push_back(tex);
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
=======
				int colorChange = entity["AI"]["colorChange"].GetInt();
				int movement = entity["AI"]["movement"].GetInt();
				float speed = entity["AI"]["speed"].GetFloat();
				float range = entity["AI"]["range"].GetFloat();

				e.AddComponent<AI>({ colorChange ,movement, speed , range });
			}
			if (entity.HasMember("Text")) {
				Text text;
				text.fontFile = entity["Text"]["fontFile"].GetString();
				text.text = entity["Text"]["text"].GetString();
				text.offset = GetVec2(entity["Text"]["offset"]);
				text.scale = entity["Text"]["scale"].GetFloat();
				text.color.r = (GLubyte)entity["Text"]["color"]["r"].GetInt();
				text.color.g = (GLubyte)entity["Text"]["color"]["g"].GetInt();
				text.color.b = (GLubyte)entity["Text"]["color"]["b"].GetInt();
				text.color.a = (GLubyte)entity["Text"]["color"]["a"].GetInt();
				e.AddComponent<Text>(text);
			}
			if (entity.HasMember("Dialogue")) {
				Dialogue dialogue;
				dialogue.speakerID = (GLubyte)entity["Dialogue"]["speakerID"].GetInt();
				dialogue.selectedID = (GLubyte)entity["Dialogue"]["selectedID"].GetInt();
				dialogue.textID = (GLubyte)entity["Dialogue"]["textID"].GetInt();
				dialogue.nextTextID = (GLubyte)entity["Dialogue"]["nextTextID"].GetInt();
				e.AddComponent<Dialogue>(dialogue);
			}
			if (entity.HasMember("LightSource")) {
				LightSource lightSource;
				lightSource.centerOffset = GetVec2(entity["LightSource"]["centerOffset"]);
				e.AddComponent<LightSource>(lightSource);
			}
			if (entity.HasMember("Script")) {
				Script script;
				script.name = entity["Script"]["name"].GetString();
				//script.script = nullptr;

				e.AddComponent<Script>(script);
			}
			//mEntities.insert(e);
			_sceneData.mEntities.insert(e);
			i++;
>>>>>>> Stashed changes
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
		if (entity.HasMember("AI"))
		{
			int colorChange = entity["AI"]["colorChange"].GetInt();
			int movement = entity["AI"]["movement"].GetInt();
			float speed = entity["AI"]["speed"].GetFloat();
			float range = entity["AI"]["range"].GetFloat();

			e.AddComponent<Stuff>({ colorChange ,movement, speed , range });
		}
		mEntities.insert(e);
		i++;
	}
}
<<<<<<< Updated upstream
=======
Point2DCollider SerializationManager::getPoint2DCollider(Value& entity)
{
	Point2DCollider point2DCollider;
	point2DCollider.centerOffset = GetVec2(entity["Point2DCollider"]["centerOffset"]);
	point2DCollider.renderFlag = entity["Point2DCollider"]["renderFlag"].GetBool();
	return point2DCollider;
}
Audio SerializationManager::getAudio(Value& entity)
{
	Audio audio;
	Sound sound;
	sound.path = entity["Audio"]["path"].GetString();
	sound.volume = entity["Audio"]["volume"].GetFloat();
	sound.volumeMod = entity["Audio"]["volumeMod"].GetFloat();
	sound.pitch = entity["Audio"]["pitch"].GetFloat();
	sound.isPaused = entity["Audio"]["isPaused"].GetBool();
	sound.isMute = entity["Audio"]["isMute"].GetBool();
	sound.isLoop = entity["Audio"]["isLoop"].GetBool();
	sound.isRandPitch = entity["Audio"]["isRandPitch"].GetBool();
	audio.sound = sound;
	audio.isSpacial = entity["Audio"]["isSpacial"].GetBool();
	return audio;
}
AI SerializationManager::getAI(Value& entity)
{
	AI ai;
	ai.colorChange = entity["AI"]["colorChange"].GetInt();
	ai.movement = entity["AI"]["movement"].GetInt();
	ai.speed = entity["AI"]["speed"].GetFloat();
	ai.range = entity["AI"]["range"].GetFloat();
	return ai;
}
Text SerializationManager::getText(Value& entity)
{
	Text text;
	text.fontFile = entity["Text"]["fontFile"].GetString();
	text.text = entity["Text"]["text"].GetString();
	text.offset = GetVec2(entity["Text"]["offset"]);
	text.scale = entity["Text"]["scale"].GetFloat();
	text.color.r = (GLubyte)entity["Text"]["color"]["r"].GetInt();
	text.color.g = (GLubyte)entity["Text"]["color"]["g"].GetInt();
	text.color.b = (GLubyte)entity["Text"]["color"]["b"].GetInt();
	text.color.a = (GLubyte)entity["Text"]["color"]["a"].GetInt();
	return text;
}
Dialogue SerializationManager::getDialogue(Value& entity)
{
	Dialogue dialogue;
	dialogue.speakerID = (GLubyte)entity["Dialogue"]["speakerID"].GetInt();
	dialogue.selectedID = (GLubyte)entity["Dialogue"]["selectedID"].GetInt();
	dialogue.textID = (GLubyte)entity["Dialogue"]["textID"].GetInt();
	dialogue.nextTextID = (GLubyte)entity["Dialogue"]["nextTextID"].GetInt();
	return dialogue;
}
LightSource SerializationManager::getLightSource(Value& entity)
{
	LightSource lightSource;
	lightSource.centerOffset = GetVec2(entity["LightSource"]["centerOffset"]);
	return lightSource;
}
Script SerializationManager::getScript(Value& entity)
{
	Script script;
	script.name = entity["Script"]["name"].GetString();
	//script.script = nullptr;
	return script;
}
Button SerializationManager::getButton(Value& entity)
{
	Button button;
	button.interactable = entity["Button"]["interactable"].GetBool();
	return button;
}






>>>>>>> Stashed changes

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
	Adds a string vector to a rapid jason dom tree as a array
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
void addVectorArrayStrMember(Document& scene, Value& parent, const char* name, std::vector <T> data)
{
	Value child(kObjectType);
	child.SetArray();
	for (size_t i = 0; i < data.size(); ++i)
	{
		std::string tex = spriteManager->GetTexturePath(data[i]);
		Value texpath(tex.c_str(), (SizeType)tex.size(), scene.GetAllocator());
		child.PushBack(texpath, scene.GetAllocator());
	}
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
	//Writer<StringBuffer> writer(buffer);
	PrettyWriter<StringBuffer> writer(buffer);
	int counter = 0;
	
	for (const Entity& e : mEntities)
	{
		if (!e.HasComponent<General>())
			continue;
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
			std::string tex = spriteManager->GetTexturePath(spriteManager->GetTexture(e));
			Value texpath(tex.c_str(), (SizeType)tex.size(), allocator);
			tmp.AddMember(StringRef("texture"), texpath, allocator);
			tmp.AddMember(StringRef("layer"), e.GetComponent<Sprite>().layer, allocator);
			entity.AddMember(StringRef("Sprite"), tmp, allocator);
		}
		if (e.HasComponent<Animation>())
		{
			Value tmp(kObjectType);
			addVectorArrayStrMember(scene, tmp, "images", e.GetComponent<Animation>().images);
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
		if (e.HasComponent<Stuff>())
		{
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("colorChange"), e.GetComponent<Stuff>().colorChange, allocator);
			tmp.AddMember(StringRef("movement"), e.GetComponent<Stuff>().movement, allocator);
			tmp.AddMember(StringRef("speed"), e.GetComponent<Stuff>().speed, allocator);
			tmp.AddMember(StringRef("range"), e.GetComponent<Stuff>().range, allocator);
			entity.AddMember(StringRef("AI"), tmp, allocator);
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
		LOG_INFO("Saved Scene: " + path);
}
<<<<<<< Updated upstream
=======
/*!*****************************************************************************
\brief
	Saves each component into rapid json
\param scene
	rapid jason document to add to
\param entity
	parent onject to add to
\prama general
	data to be added to the child objects
\return
None.
*******************************************************************************/
void SerializationManager::addGeneral(Document& scene, Value& entity, General general)
{
	Value tmp(kObjectType);
	Value vname(general.name.c_str(), (SizeType)general.name.size(), scene.GetAllocator());
	tmp.AddMember(StringRef("name"), vname, scene.GetAllocator());
	tmp.AddMember(StringRef("tag"), (int)general.tag, scene.GetAllocator());
	tmp.AddMember(StringRef("subtag"), (int)general.subtag, scene.GetAllocator());
	tmp.AddMember(StringRef("isActive"), general.isActive, scene.GetAllocator());
	entity.AddMember(StringRef("General"), tmp, scene.GetAllocator());
}
void SerializationManager::addLifespan(Document& scene, Value& entity, Lifespan lifespan)
{
	Value tmp(kObjectType);
	tmp.AddMember(StringRef("limit"), lifespan.limit, scene.GetAllocator());
	tmp.AddMember(StringRef("lifetime"), lifespan.lifetime, scene.GetAllocator());
	entity.AddMember(StringRef("Lifespan"), tmp, scene.GetAllocator());
}
void SerializationManager::addTransform(Document& scene, Value& entity, Transform transform)
{
	Value tmp(kObjectType);
	addVectorMember(scene, tmp, "scale", transform.scale);
	tmp.AddMember(StringRef("rotation"), transform.rotation, scene.GetAllocator());
	addVectorMember(scene, tmp, "translation", transform.translation);
	entity.AddMember(StringRef("Transform"), tmp, scene.GetAllocator());
}
void SerializationManager::addSprite(Document& scene, Value& entity, Sprite sprite)
{
	Value tmp(kObjectType);
	Value tmpc(kObjectType);
	tmpc.AddMember(StringRef("r"), sprite.color.r, scene.GetAllocator());
	tmpc.AddMember(StringRef("g"), sprite.color.g, scene.GetAllocator());
	tmpc.AddMember(StringRef("b"), sprite.color.b, scene.GetAllocator());
	tmpc.AddMember(StringRef("a"), sprite.color.a, scene.GetAllocator());
	tmp.AddMember(StringRef("color"), tmpc, scene.GetAllocator());
	tmp.AddMember(StringRef("sprite"), (int)sprite.sprite, scene.GetAllocator());
	std::string tex = spriteManager->GetTexturePath(sprite.texture);
	Value vtexture(tex.c_str(), (SizeType)tex.size(), scene.GetAllocator());
	tmp.AddMember(StringRef("texture"), vtexture, scene.GetAllocator());
	tmp.AddMember(StringRef("layer"), sprite.layer, scene.GetAllocator());
	entity.AddMember(StringRef("Sprite"), tmp, scene.GetAllocator());
}
void SerializationManager::addAnimation(Document& scene, Value& entity, Animation animation)
{
	Value tmp(kObjectType);
	addVectorArrayStrMember(scene, tmp, "images", animation.images);
	tmp.AddMember(StringRef("timePerImage"), animation.timePerImage, scene.GetAllocator());
	tmp.AddMember(StringRef("timeToImageSwap"), animation.timeToImageSwap, scene.GetAllocator());
	tmp.AddMember(StringRef("currentImageIndex"), animation.currentImageIndex, scene.GetAllocator());
	entity.AddMember(StringRef("Animation"), tmp, scene.GetAllocator());
}
void SerializationManager::addSheetAnimation(Document& scene, Value& entity, SheetAnimation sheetAnimation)
{
	Value tmp(kObjectType);
	tmp.AddMember(StringRef("frameCount"), sheetAnimation.frameCount, scene.GetAllocator());
	tmp.AddMember(StringRef("currFrameIndex"), sheetAnimation.currFrameIndex, scene.GetAllocator());
	tmp.AddMember(StringRef("timePerFrame"), sheetAnimation.timePerFrame, scene.GetAllocator());
	tmp.AddMember(StringRef("timeToFrameSwap"), sheetAnimation.timeToFrameSwap, scene.GetAllocator());
	entity.AddMember(StringRef("SheetAnimation"), tmp, scene.GetAllocator());
}
void SerializationManager::addPhysics2D(Document& scene, Value& entity, Physics2D physics2D)
{
	Value tmp(kObjectType);
	tmp.AddMember(StringRef("dynamicsEnabled"), physics2D.dynamicsEnabled, scene.GetAllocator());
	tmp.AddMember(StringRef("mass"), physics2D.mass, scene.GetAllocator());
	tmp.AddMember(StringRef("inertia"), physics2D.inertia, scene.GetAllocator());
	tmp.AddMember(StringRef("restitution"), physics2D.restitution, scene.GetAllocator());
	tmp.AddMember(StringRef("friction"), physics2D.friction, scene.GetAllocator());
	tmp.AddMember(StringRef("damping"), physics2D.damping, scene.GetAllocator());

	addVectorMember(scene, tmp, "accumulatedForce", physics2D.accumulatedForce);
	addVectorMember(scene, tmp, "velocity", physics2D.velocity);
	addVectorMember(scene, tmp, "acceleration", physics2D.acceleration);

	tmp.AddMember(StringRef("angularVelocity"), physics2D.angularVelocity, scene.GetAllocator());
	tmp.AddMember(StringRef("angularTorque"), physics2D.angularTorque, scene.GetAllocator());

	addVectorArrayForceMember(scene, tmp, "forceList", physics2D.forceList);


	tmp.AddMember(StringRef("renderFlag"), physics2D.renderFlag, scene.GetAllocator());
	entity.AddMember(StringRef("Physics2D"), tmp, scene.GetAllocator());
}
void SerializationManager::addRectCollider(Document& scene, Value& entity, RectCollider rectCollider)
{
	Value tmp(kObjectType);
	addVectorMember(scene, tmp, "centerOffset", rectCollider.centerOffset);
	addVectorMember(scene, tmp, "scaleOffset", rectCollider.scaleOffset);
	tmp.AddMember(StringRef("isTrigger"), rectCollider.isTrigger, scene.GetAllocator());
	tmp.AddMember(StringRef("renderFlag"), rectCollider.renderFlag, scene.GetAllocator());
	entity.AddMember(StringRef("RectCollider"), tmp, scene.GetAllocator());
}
void SerializationManager::addLayerCollider(Document& scene, Value& entity, LayerCollider layerCollider)
{
	Value tmp(kObjectType);
	addVectorMember(scene, tmp, "centerOffset", layerCollider.centerOffset);
	addVectorMember(scene, tmp, "scaleOffset", layerCollider.scaleOffset);
	tmp.AddMember(StringRef("renderFlag"), layerCollider.renderFlag, scene.GetAllocator());
	entity.AddMember(StringRef("LayerCollider"), tmp, scene.GetAllocator());
}
void SerializationManager::addCircleCollider(Document& scene, Value& entity, CircleCollider circleCollider)
{
	Value tmp(kObjectType);
	addVectorMember(scene, tmp, "centerOffset", circleCollider.centerOffset);
	tmp.AddMember(StringRef("scaleOffset"), circleCollider.scaleOffset, scene.GetAllocator());
	tmp.AddMember(StringRef("isTrigger"), circleCollider.isTrigger, scene.GetAllocator());
	tmp.AddMember(StringRef("renderFlag"), circleCollider.renderFlag, scene.GetAllocator());
	entity.AddMember(StringRef("CircleCollider"), tmp, scene.GetAllocator());
}
void SerializationManager::addEdge2DCollider(Document& scene, Value& entity, Edge2DCollider edge2DCollider)
{
	Value tmp(kObjectType);
	addVectorMember(scene, tmp, "p0Offset", edge2DCollider.p0Offset);
	tmp.AddMember(StringRef("rotationOffset"), edge2DCollider.rotationOffset, scene.GetAllocator());
	tmp.AddMember(StringRef("scaleOffset"), edge2DCollider.scaleOffset, scene.GetAllocator());
	tmp.AddMember(StringRef("renderFlag"), edge2DCollider.renderFlag, scene.GetAllocator());
	entity.AddMember(StringRef("Edge2DCollider"), tmp, scene.GetAllocator());
}
void SerializationManager::addPoint2DCollider(Document& scene, Value& entity, Point2DCollider point2DCollider)
{
	Value tmp(kObjectType);
	addVectorMember(scene, tmp, "centerOffset", point2DCollider.centerOffset);
	tmp.AddMember(StringRef("renderFlag"), point2DCollider.renderFlag, scene.GetAllocator());
	entity.AddMember(StringRef("Point2DCollider"), tmp, scene.GetAllocator());
}
void SerializationManager::addAudio(Document& scene, Value& entity, Audio audio)
{
	Value tmp(kObjectType);
	Value vpath(audio.sound.path.c_str(), (SizeType)audio.sound.path.size(), scene.GetAllocator());
	tmp.AddMember(StringRef("path"), vpath, scene.GetAllocator());
	tmp.AddMember(StringRef("volume"), audio.sound.volume, scene.GetAllocator());
	tmp.AddMember(StringRef("volumeMod"), audio.sound.volumeMod, scene.GetAllocator());
	tmp.AddMember(StringRef("pitch"), audio.sound.pitch, scene.GetAllocator());
	tmp.AddMember(StringRef("isPaused"), audio.sound.isPaused, scene.GetAllocator());
	tmp.AddMember(StringRef("isMute"), audio.sound.isMute, scene.GetAllocator());
	tmp.AddMember(StringRef("isLoop"), audio.sound.isLoop, scene.GetAllocator());
	tmp.AddMember(StringRef("isRandPitch"), audio.sound.isRandPitch, scene.GetAllocator());
	tmp.AddMember(StringRef("isSpacial"), audio.isSpacial, scene.GetAllocator());
	entity.AddMember(StringRef("Audio"), tmp, scene.GetAllocator());
}
void SerializationManager::addAI(Document& scene, Value& entity, AI ai)
{
	Value tmp(kObjectType);
	tmp.AddMember(StringRef("colorChange"), ai.colorChange, scene.GetAllocator());
	tmp.AddMember(StringRef("movement"), ai.movement, scene.GetAllocator());
	tmp.AddMember(StringRef("speed"), ai.speed, scene.GetAllocator());
	tmp.AddMember(StringRef("range"), ai.range, scene.GetAllocator());
	entity.AddMember(StringRef("AI"), tmp, scene.GetAllocator());
}
void SerializationManager::addText(Document& scene, Value& entity, Text text)
{
	Value tmp(kObjectType);
	Value tmpc(kObjectType);
	Value vfontFile(text.fontFile.c_str(), (SizeType)text.fontFile.size(), scene.GetAllocator());
	tmp.AddMember(StringRef("fontFile"), vfontFile, scene.GetAllocator());
	Value vtext(text.text.c_str(), (SizeType)text.text.size(), scene.GetAllocator());
	tmp.AddMember(StringRef("text"), vtext, scene.GetAllocator());
	addVectorMember(scene, tmp, "offset", text.offset);
	tmp.AddMember(StringRef("scale"), text.scale, scene.GetAllocator());
	tmpc.AddMember(StringRef("r"), text.color.r, scene.GetAllocator());
	tmpc.AddMember(StringRef("g"), text.color.g, scene.GetAllocator());
	tmpc.AddMember(StringRef("b"), text.color.b, scene.GetAllocator());
	tmpc.AddMember(StringRef("a"), text.color.a, scene.GetAllocator());
	tmp.AddMember(StringRef("color"), tmpc, scene.GetAllocator());
	entity.AddMember(StringRef("Text"), tmp, scene.GetAllocator());
}
void SerializationManager::addDialogue(Document& scene, Value& entity, Dialogue dialogue)
{
	Value tmp(kObjectType);
	tmp.AddMember(StringRef("speakerID"), dialogue.speakerID, scene.GetAllocator());
	tmp.AddMember(StringRef("selectedID"), dialogue.selectedID, scene.GetAllocator());
	tmp.AddMember(StringRef("textID"), dialogue.textID, scene.GetAllocator());
	tmp.AddMember(StringRef("nextTextID"), dialogue.nextTextID, scene.GetAllocator());
	entity.AddMember(StringRef("Dialogue"), tmp, scene.GetAllocator());
}
void SerializationManager::addLightSource(Document& scene, Value& entity, LightSource lightSource)
{
	Value tmp(kObjectType);
	addVectorMember(scene, tmp, "centerOffset", lightSource.centerOffset);
	entity.AddMember(StringRef("LightSource"), tmp, scene.GetAllocator());
}
void SerializationManager::addScript(Document& scene, Value& entity, Script script)
{
	Value tmp(kObjectType);
	Value spath(script.name.c_str(), (SizeType)script.name.size(), scene.GetAllocator());
	tmp.AddMember(StringRef("name"), spath, scene.GetAllocator());
	entity.AddMember(StringRef("Script"), tmp, scene.GetAllocator());
}
void SerializationManager::addButton(Document& scene, Value& entity, Button button)
{
	Value tmp(kObjectType);
	tmp.AddMember(StringRef("interactable"), button.interactable, scene.GetAllocator());
	entity.AddMember(StringRef("Button"), tmp, scene.GetAllocator());
}

/*!*****************************************************************************
\brief
	Load the saved gamestate data
\param _gameState
	gameState to load to
\param _filename
   path to load from
\return
None.
*******************************************************************************/
void SerializationManager::LoadGameState(GameState& _gameState, std::filesystem::path _filename)
{
	//GameState gameStateData{};
	//std::vector<std::string> scenefilename{};
	//std::string path = "../resources/GameStates/" + _filename + ".json";
	//std::ifstream ifs(path);
	
	std::ifstream ifs(_filename.string());
	if (!ifs.good())
	{
		LOG_ERROR("Can't open json file! : " + _filename.stem().string());
		return;
	}
	else
		LOG_INFO("Opening game state: " + _filename.stem().string());
	_gameState.mName = _filename.stem().string();

	int same = 0;
	//for (std::string s : allgameStateFilename)
	for (GameState& g : GameStateManager::GetInstance()->mGameStates)
	{
		if (g.mName == _gameState.mName)
			same++;
	}
	allgameStateFilename.push_back(_gameState.mName);
	if (same > 1)//gamestate already open
	{
		same = 0; //count number of open GS
		for (std::string n : allgameStateFilename)
		{
			if (n == _gameState.mName)
				same++;
		}
		_gameState.mName += (" ("+ std::to_string(same) + ")");
	}
	
	gameStateFilename = _gameState.mName;
	std::stringstream contents;
	contents << ifs.rdbuf();
	Document doc;
	doc.Parse(contents.str().c_str());

	Value entity(kArrayType);
	entity = doc.GetArray();
	for (rapidjson::SizeType index = 0; index < entity.Size(); ++index)
	{
		Scene sceneData(entity[index]["SceneName"].GetString());
		//sceneData.mName = entity[index]["SceneName"].GetString();
		sceneData.mCamera = getTransform(entity[index]);
		sceneData.mIsPause = entity[index]["isActive"].GetBool();
		sceneData.mLayer = entity[index]["layer"].GetInt();
		sceneData.mOrder = entity[index]["order"].GetInt();


		_gameState.mScenes.push_back(sceneData);
	}
	ifs.close();
	//return gameStateData;
}
/*!*****************************************************************************
\brief
	Save the gamestate data
\param _gameState
	gameState to save from
\return
None.
*******************************************************************************/
void SerializationManager::SaveGameState(GameState& _gameState)
{

	//scave each scene
	for (int s = 0; s< _gameState.mScenes.size(); s++)
	{
		SaveScene(_gameState.mScenes[s]);
		LOG_INFO("Saved a scene");
	}
	Document gamestate;
	auto& allocator = gamestate.GetAllocator();
	//scene.SetObject();
	gamestate.SetArray();
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	//int counter = 0;
	for (int s = 0; s< _gameState.mScenes.size(); s++)
	{

		Value scene(kObjectType);
		Value sceneName(_gameState.mScenes[s].mName.c_str(), (SizeType)_gameState.mScenes[s].mName.size(), allocator);
		scene.AddMember(StringRef("SceneName"), sceneName, gamestate.GetAllocator());
		addTransform(gamestate, scene, _gameState.mScenes[s].mCamera);
		scene.AddMember(StringRef("isActive"), _gameState.mScenes[s].mIsPause, gamestate.GetAllocator());
		scene.AddMember(StringRef("layer"), _gameState.mScenes[s].mLayer, gamestate.GetAllocator());
		scene.AddMember(StringRef("order"), _gameState.mScenes[s].mOrder, gamestate.GetAllocator());
		gamestate.PushBack(scene, allocator);
	}

	gamestate.Accept(writer);
	std::string jsonf(buffer.GetString(), buffer.GetSize());
	std::string path = "../resources/GameStates/" + _gameState.mName + ".json";
	std::ofstream ofs(path);
	ofs << jsonf;
	if (!ofs.good())
	{
		LOG_ERROR("Unable to save Game State to: " + path);
	}
	else
		LOG_INFO("Saved Game State: " + path);



}








>>>>>>> Stashed changes

/*!*****************************************************************************
\brief
	Loads the dialogs from a json file to the dialog manager

\return
None.
*******************************************************************************/
void SerializationManager::LoadDialogs(std::string _filename)
{
	std::ifstream ifs("../resources/Dialogs/" + _filename + ".json");
	if (!ifs.good())
		LOG_ERROR("Can't open " + _filename + ".json file!");
	else {
		LOG_INFO("Opened dialog json file: " + _filename);

		std::stringstream contents;
		contents << ifs.rdbuf();
		Document json;
		json.Parse(contents.str().c_str());

		//std::cout << "contents.str() " << contents.str() << '\n';
		int dialogId;
		Dialog dialog;
		Value dialogObj(kArrayType);
		dialogObj = json.GetArray();
		for (rapidjson::SizeType index = 0; index < dialogObj.Size(); ++index) {
			dialogId = dialogObj[index]["Dialogue ID"].GetInt();
			dialog.text = dialogObj[index]["Dialogue Text"].GetString();
			//std::cout << "dialog.text " << dialog.text << '\n';
			dialog.speaker = dialogObj[index]["Speaker"].GetInt();
			dialog.next = dialogObj[index]["Next Dialogue"].GetInt();
			dialog.next2 = dialogObj[index]["Next Dialogue(2)"].GetInt();
			dialogManager->LoadDialog(dialogId, dialog);
		}
	}
}
/*!*****************************************************************************
\brief
	Saves the data in the dialog manager to a json file

\return
None.
*******************************************************************************/
void SerializationManager::SaveDialogs(std::string _filename)
{
	Document json;
	auto& allocator = json.GetAllocator();
	json.SetArray();
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	Value temp(kObjectType);
	for (std::pair<int, Dialog> dialog : dialogManager->GetDialogs()){
		Value dialogObj(kObjectType);
		std::string text = dialog.second.text;
		Value dText(text.c_str(), (SizeType)text.size(), allocator);
		dialogObj.AddMember(StringRef("Dialogue ID"), (int)dialog.first, allocator);
		dialogObj.AddMember(StringRef("Dialogue Text"), dText, allocator);
		dialogObj.AddMember(StringRef("Speaker"), (int)dialog.second.speaker, allocator);
		dialogObj.AddMember(StringRef("Next Dialogue"), (int)dialog.second.next, allocator);
		dialogObj.AddMember(StringRef("Next Dialogue(2)"), (int)dialog.second.next2, allocator);
		json.PushBack(dialogObj, allocator);
	}
	json.Accept(writer);
	std::string jsonf(buffer.GetString(), buffer.GetSize());
	std::string path = "../resources/Dialogs/" + _filename + ".json";
	std::ofstream ofs(path);
	ofs << jsonf;
	if (!ofs.good()) LOG_ERROR("Unable to save dialogue file to: " + path);
	else LOG_INFO("Saved dialogue file: " + path);
}