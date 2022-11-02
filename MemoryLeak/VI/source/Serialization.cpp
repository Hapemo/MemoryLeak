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
	std::stringstream contents;
	contents << ifs.rdbuf();
	Document doc;
	doc.Parse(contents.str().c_str());

	//std::cout << contents.str() << '\n';

	int i = 0;
	//int runOnce{};
	for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr <= doc.MemberEnd(); ++itr)
	{
		//if (!runOnce++) continue;
		std::string header = "SceneData";
		Value head(header.c_str(), (SizeType)header.size(), doc.GetAllocator());
		
		Entity e{ ECS::CreateEntity() };
		Value entity(kObjectType);
		std::string str("Entity" + std::to_string(i));
		Value index(str.c_str(), (SizeType)str.size(), doc.GetAllocator());
		if (!doc.HasMember(index))
		{
			if (doc.HasMember(head))
			{
				continue;
			}
			LOG_INFO("1 Enitity not loaded");
			
			continue;
		}
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
		}
		if (entity.HasMember("Physics2D")) {

			bool dynamicsEnabled = entity["Physics2D"]["dynamicsEnabled"].GetBool();
			float mass = entity["Physics2D"]["mass"].GetFloat();
			float inertia = entity["Physics2D"]["inertia"].GetFloat();
			float restitution = entity["Physics2D"]["restitution"].GetFloat();
			float friction = entity["Physics2D"]["friction"].GetFloat();
			float damping = entity["Physics2D"]["damping"].GetFloat();

			Math::Vec2 accumulatedForce = GetVec2(entity["Physics2D"]["accumulatedForce"]);
			Math::Vec2 velocity = GetVec2(entity["Physics2D"]["velocity"]);
			Math::Vec2 acceleration = GetVec2(entity["Physics2D"]["acceleration"]);

			float angularVelocity = entity["Physics2D"]["angularVelocity"].GetFloat();
			float angularTorque = entity["Physics2D"]["angularTorque"].GetFloat();

			//vect force
			std::vector<Force> forceList{};
			Value a(kObjectType);
			a = entity["Physics2D"]["forceList"].GetArray();
			for (int j = 0; j < (int)a.Size(); ++j)
			{
				Force force{};
				Value f(kObjectType);
				f = a[j].GetObject();
				force.lifetimeLimit = f["lifetimeLimit"].GetDouble();
				force.age = f["age"].GetDouble();
				force.isActive = f["isActive"].GetBool();
				force.forceID = f["forceID"].GetInt();
				if (force.forceID == 0)
				{
					force.linearForce.unitDirection = GetVec2(f["linearForce"]["unitDirection"]);
					force.linearForce.magnitude = f["linearForce"]["magnitude"].GetFloat();
				}
				else if (force.forceID == 1)
				{
					force.rotationalForce.torque = f["rotationalForce"]["torque"].GetFloat();
				}
				else if (force.forceID == 2)
				{
					force.dragForce.directionalDrag = f["dragForce"]["directionalDrag"].GetFloat();
					force.dragForce.rotationalDrag = f["dragForce"]["rotationalDrag"].GetFloat();
				}

				forceList.push_back(force);
			}

			bool renderFlag = entity["Physics2D"]["renderFlag"].GetBool();

			e.AddComponent<Physics2D>({ dynamicsEnabled, mass, inertia, restitution, friction, damping, accumulatedForce,velocity, acceleration, angularVelocity, angularTorque, forceList, renderFlag });
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
			lightSource.centreOffset = GetVec2(entity["LightSource"]["centerOffset"]);
			e.AddComponent<LightSource>(lightSource);
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
template<typename T>
void addVectorArrayForceMember(Document& scene, Value& parent, const char* name, std::vector <T> data)
{
	Value child(kObjectType);
	child.SetArray();
	for (size_t i = 0; i < data.size(); ++i)
	{
		Force force = data[i];
		Value childitems(kObjectType);

		childitems.AddMember(StringRef("lifetimeLimit"), data[i].lifetimeLimit, scene.GetAllocator());
		childitems.AddMember(StringRef("age"), data[i].age, scene.GetAllocator());
		childitems.AddMember(StringRef("isActive"), data[i].isActive, scene.GetAllocator());
		childitems.AddMember(StringRef("forceID"), data[i].forceID, scene.GetAllocator());
		Value grandchilditems(kObjectType);
		if (data[i].forceID == 0)
		{
			addVectorMember(scene, grandchilditems, "unitDirection", data[i].linearForce.unitDirection);
			grandchilditems.AddMember(StringRef("magnitude"), data[i].linearForce.magnitude, scene.GetAllocator());
		}
		else if (data[i].forceID==1)
		{
			grandchilditems.AddMember(StringRef("torque"), data[i].rotationalForce.torque, scene.GetAllocator());
		}
		else if (data[i].forceID==2)
		{
			grandchilditems.AddMember(StringRef("directionalDrag"), data[i].dragForce.directionalDrag, scene.GetAllocator());
			grandchilditems.AddMember(StringRef("rotationalDrag"), data[i].dragForce.rotationalDrag, scene.GetAllocator());
			childitems.AddMember(StringRef("color"), grandchilditems, scene.GetAllocator());
		}
		
		child.PushBack(childitems, scene.GetAllocator());
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
		if (e.HasComponent<Physics2D>()) {
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("dynamicsEnabled"), e.GetComponent<Physics2D>().dynamicsEnabled, allocator);
			tmp.AddMember(StringRef("mass"), e.GetComponent<Physics2D>().mass, allocator);
			tmp.AddMember(StringRef("inertia"), e.GetComponent<Physics2D>().inertia, allocator);
			tmp.AddMember(StringRef("restitution"), e.GetComponent<Physics2D>().restitution, allocator);
			tmp.AddMember(StringRef("friction"), e.GetComponent<Physics2D>().friction, allocator);
			tmp.AddMember(StringRef("damping"), e.GetComponent<Physics2D>().damping, allocator);

			addVectorMember(scene, tmp, "accumulatedForce", e.GetComponent<Physics2D>().accumulatedForce);
			addVectorMember(scene, tmp, "velocity", e.GetComponent<Physics2D>().velocity);
			addVectorMember(scene, tmp, "acceleration", e.GetComponent<Physics2D>().acceleration);

			tmp.AddMember(StringRef("angularVelocity"), e.GetComponent<Physics2D>().angularVelocity, allocator);
			tmp.AddMember(StringRef("angularTorque"), e.GetComponent<Physics2D>().angularTorque, allocator);

			addVectorArrayForceMember(scene, tmp, "forceList", e.GetComponent<Physics2D>().forceList);


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
		if (e.HasComponent<AI>())
		{
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("colorChange"), e.GetComponent<AI>().colorChange, allocator);
			tmp.AddMember(StringRef("movement"), e.GetComponent<AI>().movement, allocator);
			tmp.AddMember(StringRef("speed"), e.GetComponent<AI>().speed, allocator);
			tmp.AddMember(StringRef("range"), e.GetComponent<AI>().range, allocator);
			entity.AddMember(StringRef("AI"), tmp, allocator);
		}
		if (e.HasComponent<Text>()) {
			Value tmp(kObjectType);
			Value tmpc(kObjectType);
			tmp.AddMember(StringRef("fontFile"), StringRef(e.GetComponent<Text>().fontFile.c_str()), allocator);
			tmp.AddMember(StringRef("text"), StringRef(e.GetComponent<Text>().text.c_str()), allocator);
			addVectorMember(scene, tmp, "offset", e.GetComponent<Text>().offset);
			tmp.AddMember(StringRef("scale"), e.GetComponent<Text>().scale, allocator);
			tmpc.AddMember(StringRef("r"), e.GetComponent<Text>().color.r, allocator);
			tmpc.AddMember(StringRef("g"), e.GetComponent<Text>().color.g, allocator);
			tmpc.AddMember(StringRef("b"), e.GetComponent<Text>().color.b, allocator);
			tmpc.AddMember(StringRef("a"), e.GetComponent<Text>().color.a, allocator);
			tmp.AddMember(StringRef("color"), tmpc, allocator);
			entity.AddMember(StringRef("Text"), tmp, allocator);
		}
		if (e.HasComponent<Dialogue>()) {
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("speakerID"), e.GetComponent<Dialogue>().speakerID, allocator);
			tmp.AddMember(StringRef("selectedID"), e.GetComponent<Dialogue>().selectedID, allocator);
			tmp.AddMember(StringRef("textID"), e.GetComponent<Dialogue>().textID, allocator);
			tmp.AddMember(StringRef("nextTextID"), e.GetComponent<Dialogue>().nextTextID, allocator);
			entity.AddMember(StringRef("Dialogue"), tmp, allocator);
		}
		if (e.HasComponent<LightSource>()) {
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset", e.GetComponent<LightSource>().centreOffset);
			entity.AddMember(StringRef("LightSource"), tmp, allocator);
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


SceneData SerializationManager::LoadSceneData(ResourceManager::GUID const& _guid) {
	return LoadSceneData(ResourceManager::GetInstance()->GetFilePath(_guid));
}


SceneData SerializationManager::LoadSceneData(std::string const& _filePath) {
	std::ifstream ifs(_filePath);
	if (!ifs.good()) {
		LOG_ERROR("Can't open scene file: " + _filePath);
		return SceneData();
	} else LOG_INFO("Opening scene file: " + _filePath);
	std::stringstream contents;
	contents << ifs.rdbuf();
	Document doc;
	doc.Parse(contents.str().c_str());

	//std::cout << contents.str() << '\n';
	SceneData sceneData{};

	// Getting scene data from json
	std::string sceneDataName{ "SceneData" };
	Value sceneDataJson(sceneDataName.c_str(), (rapidjson::SizeType)sceneDataName.size(), doc.GetAllocator());
	if (!doc.HasMember(sceneDataJson))
	{
		std::cout << "No sceneData found in scene file!\n";
		sceneData.isActive = true;
	}
	else
	{
		Value sceneDataValue(kObjectType);
		sceneDataValue = doc[sceneDataJson];
		sceneData.isActive = sceneDataValue["isActive"].GetBool();
	}
	int i = 0;
	int runOnce{};
	for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr <= doc.MemberEnd(); ++itr) {
		if (!runOnce++) continue;

		Entity e{ ECS::CreateEntity() };
		Value entity(kObjectType);
		std::string str("Entity" + std::to_string(i));
		Value index(str.c_str(), (SizeType)str.size(), doc.GetAllocator());
		if (!doc.HasMember(index))
		{
			LOG_INFO("1 Enitity not loaded");

			continue;
		}
		entity = doc[index];

		if (entity.HasMember("General")) {
			std::string name = entity["General"]["name"].GetString();
			bool isActive = entity["General"]["isActive"].GetBool();
			int tag = entity["General"]["tag"].GetInt();
			int subtag = entity["General"]["subtag"].GetInt();
			bool isPaused = sceneData.isActive;
			e.AddComponent<General>(General{ name, (TAG)tag ,(SUBTAG)subtag, isActive, isPaused });
			if (tag == (int)TAG::PLAYER)
				e.AddComponent(PlayerTmp{ 0 });
		}
		if (entity.HasMember("Lifespan")) {
			float lifetime = entity["Lifespan"]["lifetime"].GetFloat();
			float limit = entity["Lifespan"]["limit"].GetFloat();
			e.AddComponent<Lifespan>({ lifetime, limit });
		}
		if (entity.HasMember("Transform")) {
			Math::Vec2 s = GetVec2(entity["Transform"]["scale"]);
			float r = (float)entity["Transform"]["rotation"].GetFloat();
			Math::Vec2 t = GetVec2(entity["Transform"]["translation"]);

			e.AddComponent<Transform>({ s, r, t });
		}
		if (entity.HasMember("Sprite")) {
			Color c;
			c.r = (GLubyte)entity["Sprite"]["color"]["r"].GetInt();
			c.g = (GLubyte)entity["Sprite"]["color"]["g"].GetInt();
			c.b = (GLubyte)entity["Sprite"]["color"]["b"].GetInt();
			c.a = (GLubyte)entity["Sprite"]["color"]["a"].GetInt();
			SPRITE s = (SPRITE)entity["Sprite"]["sprite"].GetInt();
			GLuint t = (GLuint)spriteManager->GetTextureID(entity["Sprite"]["texture"].GetString());
			//GLuint t = (GLuint)entity["Sprite"]["texture"].GetInt();
			int l = entity["Sprite"]["layer"].GetInt();
			e.AddComponent<Sprite>({ c, s, t ,l });
		}
		if (entity.HasMember("Animation")) {
			std::vector<GLuint> images;
			Value a(kObjectType);
			a = entity["Animation"]["images"].GetArray();
			for (int j = 0; j < (int)a.Size(); ++j) {
				GLuint tex = spriteManager->GetTextureID(a[j].GetString());
				images.push_back(tex);
			}
			float timePerImage = entity["Animation"]["timePerImage"].GetFloat();
			float timeToImageSwap = entity["Animation"]["timeToImageSwap"].GetFloat();
			int currentImageIndex = entity["Animation"]["currentImageIndex"].GetInt();
			e.AddComponent<Animation>({ images , timePerImage , timeToImageSwap , currentImageIndex });
		}
		if (entity.HasMember("SheetAnimation")) {
			short frameCount = (short)entity["SheetAnimation"]["frameCount"].GetInt();
			short currentImageIndex = (short)entity["SheetAnimation"]["currFrameIndex"].GetInt();
			float timePerImage = entity["SheetAnimation"]["timePerFrame"].GetFloat();
			float timeToImageSwap = entity["SheetAnimation"]["timeToFrameSwap"].GetFloat();
			e.AddComponent<SheetAnimation>({ frameCount , currentImageIndex , timePerImage , timeToImageSwap });
		}
		if (entity.HasMember("Physics2D")) {

			bool dynamicsEnabled = entity["Physics2D"]["dynamicsEnabled"].GetBool();
			float mass = entity["Physics2D"]["mass"].GetFloat();
			float inertia = entity["Physics2D"]["inertia"].GetFloat();
			float restitution = entity["Physics2D"]["restitution"].GetFloat();
			float friction = entity["Physics2D"]["friction"].GetFloat();
			float damping = entity["Physics2D"]["damping"].GetFloat();

			Math::Vec2 accumulatedForce = GetVec2(entity["Physics2D"]["accumulatedForce"]);
			Math::Vec2 velocity = GetVec2(entity["Physics2D"]["velocity"]);
			Math::Vec2 acceleration = GetVec2(entity["Physics2D"]["acceleration"]);

			float angularVelocity = entity["Physics2D"]["angularVelocity"].GetFloat();
			float angularTorque = entity["Physics2D"]["angularTorque"].GetFloat();

			//vect force
			std::vector<Force> forceList{};
			Value a(kObjectType);
			a = entity["Physics2D"]["forceList"].GetArray();
			for (int j = 0; j < (int)a.Size(); ++j)
			{
				Force force{};
				Value f(kObjectType);
				f = a[j].GetObject();
				force.lifetimeLimit = f["lifetimeLimit"].GetDouble();
				force.age = f["age"].GetDouble();
				force.isActive = f["isActive"].GetBool();
				force.forceID = f["forceID"].GetInt();
				if (force.forceID == 0)
				{
					force.linearForce.unitDirection = GetVec2(f["linearForce"]["unitDirection"]);
					force.linearForce.magnitude = f["linearForce"]["magnitude"].GetFloat();
				}
				else if (force.forceID == 1)
				{
					force.rotationalForce.torque = f["rotationalForce"]["torque"].GetFloat();
				}
				else if (force.forceID == 2)
				{
					force.dragForce.directionalDrag = f["dragForce"]["directionalDrag"].GetFloat();
					force.dragForce.rotationalDrag = f["dragForce"]["rotationalDrag"].GetFloat();
				}

				forceList.push_back(force);
			}

			bool renderFlag = entity["Physics2D"]["renderFlag"].GetBool();

			e.AddComponent<Physics2D>({ dynamicsEnabled, mass, inertia, restitution, friction, damping, accumulatedForce,velocity, acceleration, angularVelocity, angularTorque, forceList, renderFlag });
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
			sound.volume = entity["Audio"]["volume"].GetFloat();
			sound.volumeMod = entity["Audio"]["volumeMod"].GetFloat();
			sound.pitch = entity["Audio"]["pitch"].GetFloat();
			sound.isPaused = entity["Audio"]["isPaused"].GetBool();
			sound.isMute = entity["Audio"]["isMute"].GetBool();
			sound.isLoop = entity["Audio"]["isLoop"].GetBool();
			sound.isRandPitch = entity["Audio"]["isRandPitch"].GetBool();

			bool isSpacial = entity["Audio"]["isSpacial"].GetBool();
			e.AddComponent<Audio>({ sound , isSpacial });
		}
		if (entity.HasMember("AI"))
		{
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
			lightSource.centreOffset = GetVec2(entity["LightSource"]["centerOffset"]);
			e.AddComponent<LightSource>(lightSource);
		}
		sceneData.mEntities.insert(e);
		i++;
	}
	return sceneData;
}

GameStateData SerializationManager::LoadGameStateData(ResourceManager::GUID const& _guid) {
	return LoadGameStateData(ResourceManager::GetInstance()->GetFilePath(_guid));
}

GameStateData SerializationManager::LoadGameStateData(std::string const& _filePath) {
	std::ifstream ifs(_filePath);
	if (!ifs.good()) {
		LOG_ERROR("Can't open scene file: " + _filePath);
		return GameStateData();
	} else LOG_INFO("Opening scene file: " + _filePath);
	std::stringstream contents;
	contents << ifs.rdbuf();
	Document doc;
	doc.Parse(contents.str().c_str());

	//std::cout << contents.str() << '\n';
	GameStateData gamestateData{};

	// Getting gamestate data from json
	std::string gamestateDataName{ "GameStateData" };
	Value gamestateDataJson(gamestateDataName.c_str(), (rapidjson::SizeType)gamestateDataName.size(), doc.GetAllocator());
	if (!doc.HasMember(gamestateDataJson)) {
		std::cout << "No gamestateData found in scene file!\n";
		gamestateData.mGUIDs.push_back(0);
	}
	else
	{
		Value gamestateDataValue(kObjectType);
		gamestateDataValue = doc[gamestateDataJson];
	

		Value a(kObjectType);
		a = gamestateDataValue["Scenes"].GetArray();
		for (int j = 0; j < (int)a.Size(); ++j) {
			ResourceManager::GUID guid = a[j].GetUint64();
			gamestateData.mGUIDs.push_back(guid);
		}
	}
	
	int i = 0;
	int runOnce{0};
	for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr <= doc.MemberEnd(); ++itr) {
		if (!runOnce++) continue;

		Entity e{ ECS::CreateEntity() };
		Value entity(kObjectType);
		std::string str("Entity" + std::to_string(i));
		Value index(str.c_str(), (SizeType)str.size(), doc.GetAllocator());
		if (!doc.HasMember(index))
		{
			LOG_INFO("1 Enitity not loaded");

			continue;
		}
		entity = doc[index];

		if (entity.HasMember("General")) {
			std::string name = entity["General"]["name"].GetString();
			bool isActive = entity["General"]["isActive"].GetBool();
			int tag = entity["General"]["tag"].GetInt();
			int subtag = entity["General"]["subtag"].GetInt();
			e.AddComponent<General>(General{ name, (TAG)tag ,(SUBTAG)subtag, isActive });
			if (tag == (int)TAG::PLAYER)
				e.AddComponent(PlayerTmp{ 0 });
		}
		if (entity.HasMember("Lifespan")) {
			float lifetime = entity["Lifespan"]["lifetime"].GetFloat();
			float limit = entity["Lifespan"]["limit"].GetFloat();
			e.AddComponent<Lifespan>({ lifetime, limit });
		}
		if (entity.HasMember("Transform")) {
			Math::Vec2 s = GetVec2(entity["Transform"]["scale"]);
			float r = (float)entity["Transform"]["rotation"].GetFloat();
			Math::Vec2 t = GetVec2(entity["Transform"]["translation"]);

			e.AddComponent<Transform>({ s, r, t });
		}
		if (entity.HasMember("Sprite")) {
			Color c;
			c.r = (GLubyte)entity["Sprite"]["color"]["r"].GetInt();
			c.g = (GLubyte)entity["Sprite"]["color"]["g"].GetInt();
			c.b = (GLubyte)entity["Sprite"]["color"]["b"].GetInt();
			c.a = (GLubyte)entity["Sprite"]["color"]["a"].GetInt();
			SPRITE s = (SPRITE)entity["Sprite"]["sprite"].GetInt();
			GLuint t = (GLuint)spriteManager->GetTextureID(entity["Sprite"]["texture"].GetString());
			//GLuint t = (GLuint)entity["Sprite"]["texture"].GetInt();
			int l = entity["Sprite"]["layer"].GetInt();
			e.AddComponent<Sprite>({ c, s, t ,l });
		}
		if (entity.HasMember("Animation")) {
			std::vector<GLuint> images;
			Value ar(kObjectType);
			ar = entity["Animation"]["images"].GetArray();
			for (int j = 0; j < (int)ar.Size(); ++j) {
				GLuint tex = spriteManager->GetTextureID(ar[j].GetString());
				images.push_back(tex);
			}
			float timePerImage = entity["Animation"]["timePerImage"].GetFloat();
			float timeToImageSwap = entity["Animation"]["timeToImageSwap"].GetFloat();
			int currentImageIndex = entity["Animation"]["currentImageIndex"].GetInt();
			e.AddComponent<Animation>({ images , timePerImage , timeToImageSwap , currentImageIndex });
		}
		if (entity.HasMember("SheetAnimation")) {
			short frameCount = (short)entity["SheetAnimation"]["frameCount"].GetInt();
			short currentImageIndex = (short)entity["SheetAnimation"]["currFrameIndex"].GetInt();
			float timePerImage = entity["SheetAnimation"]["timePerFrame"].GetFloat();
			float timeToImageSwap = entity["SheetAnimation"]["timeToFrameSwap"].GetFloat();
			e.AddComponent<SheetAnimation>({ frameCount , currentImageIndex , timePerImage , timeToImageSwap });
		}
		if (entity.HasMember("Physics2D")) {

			bool dynamicsEnabled = entity["Physics2D"]["dynamicsEnabled"].GetBool();
			float mass = entity["Physics2D"]["mass"].GetFloat();
			float inertia = entity["Physics2D"]["inertia"].GetFloat();
			float restitution = entity["Physics2D"]["restitution"].GetFloat();
			float friction = entity["Physics2D"]["friction"].GetFloat();
			float damping = entity["Physics2D"]["damping"].GetFloat();

			Math::Vec2 accumulatedForce = GetVec2(entity["Physics2D"]["accumulatedForce"]);
			Math::Vec2 velocity = GetVec2(entity["Physics2D"]["velocity"]);
			Math::Vec2 acceleration = GetVec2(entity["Physics2D"]["acceleration"]);

			float angularVelocity = entity["Physics2D"]["angularVelocity"].GetFloat();
			float angularTorque = entity["Physics2D"]["angularTorque"].GetFloat();

			//vect force
			std::vector<Force> forceList{};
			Value a(kObjectType);
			a = entity["Physics2D"]["forceList"].GetArray();
			for (int j = 0; j < (int)a.Size(); ++j)
			{
				Force force{};
				Value f(kObjectType);
				f = a[j].GetObject();
				force.lifetimeLimit = f["lifetimeLimit"].GetDouble();
				force.age = f["age"].GetDouble();
				force.isActive = f["isActive"].GetBool();
				force.forceID = f["forceID"].GetInt();
				if (force.forceID == 0)
				{
					force.linearForce.unitDirection = GetVec2(f["linearForce"]["unitDirection"]);
					force.linearForce.magnitude = f["linearForce"]["magnitude"].GetFloat();
				}
				else if (force.forceID == 1)
				{
					force.rotationalForce.torque = f["rotationalForce"]["torque"].GetFloat();
				}
				else if (force.forceID == 2)
				{
					force.dragForce.directionalDrag = f["dragForce"]["directionalDrag"].GetFloat();
					force.dragForce.rotationalDrag = f["dragForce"]["rotationalDrag"].GetFloat();
				}

				forceList.push_back(force);
			}

			bool renderFlag = entity["Physics2D"]["renderFlag"].GetBool();

			e.AddComponent<Physics2D>({ dynamicsEnabled, mass, inertia, restitution, friction, damping, accumulatedForce,velocity, acceleration, angularVelocity, angularTorque, forceList, renderFlag });
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
			sound.volume = entity["Audio"]["volume"].GetFloat();
			sound.volumeMod = entity["Audio"]["volumeMod"].GetFloat();
			sound.pitch = entity["Audio"]["pitch"].GetFloat();
			sound.isPaused = entity["Audio"]["isPaused"].GetBool();
			sound.isMute = entity["Audio"]["isMute"].GetBool();
			sound.isLoop = entity["Audio"]["isLoop"].GetBool();
			sound.isRandPitch = entity["Audio"]["isRandPitch"].GetBool();

			bool isSpacial = entity["Audio"]["isSpacial"].GetBool();
			e.AddComponent<Audio>({ sound , isSpacial });
		}
		if (entity.HasMember("AI"))
		{
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
			lightSource.centreOffset = GetVec2(entity["LightSource"]["centerOffset"]);
			e.AddComponent<LightSource>(lightSource);
		}
		gamestateData.mEntities.insert(e);
		i++;
	}
	return gamestateData;
}


void SerializationManager::SaveSceneData(ResourceManager::GUID const& _guid) {
	SceneData sceneData = ResourceManager::GetInstance()->GetResource<SceneData>(_guid);

	Document scene;
	auto& allocator = scene.GetAllocator();
	scene.SetObject();

	StringBuffer buffer;
	//Writer<StringBuffer> writer(buffer);
	PrettyWriter<StringBuffer> writer(buffer);
	int counter = 0;

	// Add all scene data
	Value sceneDataValue(kObjectType);
	sceneDataValue.AddMember(StringRef("isActive"), sceneData.isActive, allocator);


	// Add all entities in the scene
	for (const Entity& e : sceneData.mEntities) {
		if (!e.HasComponent<General>())
			continue;
		Value entity(kObjectType);
		if (e.HasComponent<General>()) {
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("name"), StringRef(e.GetComponent<General>().name.c_str()), allocator);
			tmp.AddMember(StringRef("tag"), (int)e.GetComponent<General>().tag, allocator);
			tmp.AddMember(StringRef("subtag"), (int)e.GetComponent<General>().subtag, allocator);
			tmp.AddMember(StringRef("isActive"), e.GetComponent<General>().isActive, allocator);
			entity.AddMember(StringRef("General"), tmp, allocator);
		}
		if (e.HasComponent<Transform>()) {
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "scale", e.GetComponent<Transform>().scale);
			tmp.AddMember(StringRef("rotation"), e.GetComponent<Transform>().rotation, allocator);
			addVectorMember(scene, tmp, "translation", e.GetComponent<Transform>().translation);
			entity.AddMember(StringRef("Transform"), tmp, allocator);
		}
		if (e.HasComponent<Sprite>()) {
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
		if (e.HasComponent<Animation>()) {
			Value tmp(kObjectType);
			addVectorArrayStrMember(scene, tmp, "images", e.GetComponent<Animation>().images);
			tmp.AddMember(StringRef("timePerImage"), e.GetComponent<Animation>().timePerImage, allocator);
			tmp.AddMember(StringRef("timeToImageSwap"), e.GetComponent<Animation>().timeToImageSwap, allocator);
			tmp.AddMember(StringRef("currentImageIndex"), e.GetComponent<Animation>().currentImageIndex, allocator);
			entity.AddMember(StringRef("Animation"), tmp, allocator);
		}
		if (e.HasComponent<SheetAnimation>()) {
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("frameCount"), e.GetComponent<SheetAnimation>().frameCount, allocator);
			tmp.AddMember(StringRef("currFrameIndex"), e.GetComponent<SheetAnimation>().currFrameIndex, allocator);
			tmp.AddMember(StringRef("timePerFrame"), e.GetComponent<SheetAnimation>().timePerFrame, allocator);
			tmp.AddMember(StringRef("timeToFrameSwap"), e.GetComponent<SheetAnimation>().timeToFrameSwap, allocator);
			entity.AddMember(StringRef("SheetAnimation"), tmp, allocator);
		}
		if (e.HasComponent<Physics2D>()) {
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("dynamicsEnabled"), e.GetComponent<Physics2D>().dynamicsEnabled, allocator);
			tmp.AddMember(StringRef("mass"), e.GetComponent<Physics2D>().mass, allocator);
			tmp.AddMember(StringRef("inertia"), e.GetComponent<Physics2D>().inertia, allocator);
			tmp.AddMember(StringRef("restitution"), e.GetComponent<Physics2D>().restitution, allocator);
			tmp.AddMember(StringRef("friction"), e.GetComponent<Physics2D>().friction, allocator);
			tmp.AddMember(StringRef("damping"), e.GetComponent<Physics2D>().damping, allocator);

			addVectorMember(scene, tmp, "accumulatedForce", e.GetComponent<Physics2D>().accumulatedForce);
			addVectorMember(scene, tmp, "velocity", e.GetComponent<Physics2D>().velocity);
			addVectorMember(scene, tmp, "acceleration", e.GetComponent<Physics2D>().acceleration);

			tmp.AddMember(StringRef("angularVelocity"), e.GetComponent<Physics2D>().angularVelocity, allocator);
			tmp.AddMember(StringRef("angularTorque"), e.GetComponent<Physics2D>().angularTorque, allocator);
			addVectorArrayForceMember(scene, tmp, "forceList", e.GetComponent<Physics2D>().forceList);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<Physics2D>().renderFlag, allocator);
			entity.AddMember(StringRef("Physics2D"), tmp, allocator);
		}
		if (e.HasComponent<RectCollider>()) {
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset", e.GetComponent<RectCollider>().centerOffset);
			addVectorMember(scene, tmp, "scaleOffset", e.GetComponent<RectCollider>().scaleOffset);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<RectCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("RectCollider"), tmp, allocator);
		}
		if (e.HasComponent<CircleCollider>()) {
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset", e.GetComponent<CircleCollider>().centerOffset);
			tmp.AddMember(StringRef("scaleOffset"), e.GetComponent<CircleCollider>().scaleOffset, allocator);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<CircleCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("CircleCollider"), tmp, allocator);
		}
		if (e.HasComponent<Edge2DCollider>()) {
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "p0Offset", e.GetComponent<Edge2DCollider>().p0Offset);
			tmp.AddMember(StringRef("rotationOffset"), e.GetComponent<Edge2DCollider>().rotationOffset, allocator);
			tmp.AddMember(StringRef("scaleOffset"), e.GetComponent<Edge2DCollider>().scaleOffset, allocator);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<Edge2DCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("Edge2DCollider"), tmp, allocator);
		}
		if (e.HasComponent<Point2DCollider>()) {
			Value tmp(kObjectType);
			addVectorMember(scene, tmp, "centerOffset", e.GetComponent<Point2DCollider>().centerOffset);
			tmp.AddMember(StringRef("renderFlag"), e.GetComponent<Point2DCollider>().renderFlag, allocator);
			entity.AddMember(StringRef("Point2DCollider"), tmp, allocator);
		}
		if (e.HasComponent<Audio>()) {
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
		if (e.HasComponent<AI>()) {
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("colorChange"), e.GetComponent<AI>().colorChange, allocator);
			tmp.AddMember(StringRef("movement"), e.GetComponent<AI>().movement, allocator);
			tmp.AddMember(StringRef("speed"), e.GetComponent<AI>().speed, allocator);
			tmp.AddMember(StringRef("range"), e.GetComponent<AI>().range, allocator);
			entity.AddMember(StringRef("AI"), tmp, allocator);
		}
		if (e.HasComponent<Text>()) {
			Value tmp(kObjectType);
			Value tmpc(kObjectType);
			tmp.AddMember(StringRef("fontFile"), StringRef(e.GetComponent<Text>().fontFile.c_str()), allocator);
			tmp.AddMember(StringRef("text"), StringRef(e.GetComponent<Text>().text.c_str()), allocator);
			addVectorMember(scene, tmp, "offset", e.GetComponent<Text>().offset);
			tmp.AddMember(StringRef("scale"), e.GetComponent<Text>().scale, allocator);
			tmpc.AddMember(StringRef("r"), e.GetComponent<Text>().color.r, allocator);
			tmpc.AddMember(StringRef("g"), e.GetComponent<Text>().color.g, allocator);
			tmpc.AddMember(StringRef("b"), e.GetComponent<Text>().color.b, allocator);
			tmpc.AddMember(StringRef("a"), e.GetComponent<Text>().color.a, allocator);
			tmp.AddMember(StringRef("color"), tmpc, allocator);
			entity.AddMember(StringRef("Text"), tmp, allocator);
		}
		if (e.HasComponent<Dialogue>()) {
			Value tmp(kObjectType);
			tmp.AddMember(StringRef("speakerID"), e.GetComponent<Dialogue>().speakerID, allocator);
			tmp.AddMember(StringRef("selectedID"), e.GetComponent<Dialogue>().selectedID, allocator);
			tmp.AddMember(StringRef("textID"), e.GetComponent<Dialogue>().textID, allocator);
			tmp.AddMember(StringRef("nextTextID"), e.GetComponent<Dialogue>().nextTextID, allocator);
			entity.AddMember(StringRef("Dialogue"), tmp, allocator);
		}
		std::string s("Entity" + std::to_string(counter));
		Value index(s.c_str(), (SizeType)s.size(), allocator);
		scene.AddMember(index, entity, allocator);
		counter++;
	}

	scene.Accept(writer);
	std::string jsonf(buffer.GetString(), buffer.GetSize());
	std::string path = ResourceManager::GetInstance()->GetFilePath(_guid);
	std::ofstream ofs(path);
	ofs << jsonf;
	if (!ofs.good()) {
		LOG_ERROR("Unable to save scene to: " + path);
	} else
		LOG_INFO("Saved Scene: " + path);
}
