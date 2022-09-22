/*!*****************************************************************************
\file Serialization.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a Serialization system that modifies
Entities and its Components.
*******************************************************************************/
#include "Serialization.h"
#include "ECSManager.h"



using namespace rapidjson;
glm::vec2 GetVec2(Value& vecIn)
{
	glm::vec2 vecOut;
	vecOut.x = vecIn["X"].GetDouble();
	vecOut.y = vecIn["Y"].GetDouble();
	return vecOut;
}

void SerializationManager::LoadScene()
{
	std::ifstream ifs("./resources/Scene/SceneJ.json");
	if (!ifs.good())
	{
		std::cout << "cant open json file";
	}

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
		std::string s("Entity" + std::to_string(i));
		Value index(s.c_str(), s.size(), doc.GetAllocator());
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
			glm::vec2 s, t;
			float r;
			s.x = entity["Transform"]["scale"]["X"].GetDouble();
			s.y = entity["Transform"]["scale"]["Y"].GetDouble();
			r = (float)entity["Transform"]["rotation"].GetDouble();
			t.x = entity["Transform"]["translation"]["X"].GetDouble();
			t.y = entity["Transform"]["translation"]["Y"].GetDouble();
		
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
			for (int i = 0; i < a.Size(); ++i)
			{
				images.push_back((GLuint)a[i].GetInt());
			}
			float timePerImage = entity["Animation"]["timePerImage"].GetFloat();
			float timeToImageSwap = entity["Animation"]["timeToImageSwap"].GetFloat();
			int currentImageIndex = entity["Animation"]["currentImageIndex"].GetInt();
			e.AddComponent<Animation>({ images , timePerImage , timeToImageSwap , currentImageIndex });
		} 
		if (entity.HasMember("SheetAnimation"))  ////////// newwwwwwwwwwwwww
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
			bool renderFlag = entity["Physics2D"]["renderFlag"].GetBool();

			e.AddComponent<Physics2D>({ mass, speed, moveDirection, renderFlag });
			physics2DManager->AddPhysicsComponent(e, mass, speed, moveDirection, renderFlag);
		}
		if (entity.HasMember("RectCollider"))
		{
			glm::vec2 centerOffset = GetVec2(entity["RectCollider"]["centerOffset"]);
			glm::vec2	scaleOffset = GetVec2(entity["RectCollider"]["scaleOffset"]);
			bool renderFlag = entity["RectCollider"]["renderFlag"].GetBool();
			e.AddComponent<RectCollider>({ centerOffset , scaleOffset , renderFlag });
		}
		if (entity.HasMember("CircleCollider"))
		{
			glm::vec2 centerOffset = GetVec2(entity["CircleCollider"]["centerOffset"]);
			float scaleOffset = entity["CircleCollider"]["scaleOffset"].GetFloat();
			bool renderFlag = entity["CircleCollider"]["renderFlag"].GetBool();
			e.AddComponent<CircleCollider>({ centerOffset , scaleOffset , renderFlag });
		}
		/*if (entity.HasMember("Edge2DCollider"))
		{
			e.AddComponent<Edge2DCollider>({});
		}
		if (entity.HasMember("Point2DCollider"))
		{
			e.AddComponent<Point2DCollider>({});
		}*/
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


void addVectorMember(Document& scene, Value& parent, const char* name, glm::vec2 data)
{
	Value child(kObjectType);
	child.AddMember(StringRef("X"), data.x, scene.GetAllocator());
	child.AddMember(StringRef("Y"), data.y, scene.GetAllocator());
	parent.AddMember(StringRef(name), child, scene.GetAllocator());
}
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
void SerializationManager::SaveScene()
{
	std::cout << "saveing scene\n";
	Document scene ;
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
		if (e.HasComponent<SheetAnimation>())    //// newww wwwwwwwwwwwwwwwwwwwwww
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
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<Physics2D>().renderFlag, allocator);
			entity.AddMember(StringRef("Physics2D"), tmp, allocator);
		}
		if (e.HasComponent<RectCollider>())
		{
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset", e.GetComponent<RectCollider>().centerOffset);
			addVectorMember(scene, tmp, "scaleOffset", e.GetComponent<RectCollider>().scaleOffset);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<RectCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("RectCollider"), tmp, allocator);
		}
		if (e.HasComponent<CircleCollider>())
		{
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset", e.GetComponent<CircleCollider>().centerOffset);
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
		/*if (e.HasComponent<Point2DCollider>())
		{
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset", e.GetComponent<Point2DCollider>().centerOffset);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<Point2DCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("Point2DCollider"), tmp, allocator);
		}*/
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
	std::ofstream ofs("./resources/Scene/SceneJ.json");
	ofs << jsonf;
	if (!ofs.good() )
	{
		std::cout << "json errorrr";
	}
}
void SerializationManager::LoadDialogs()
{

}
void SerializationManager::SaveDialogs()
{

}