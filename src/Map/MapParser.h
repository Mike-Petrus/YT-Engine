#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "../Vendor/TinyXML/tinyxml.h"
#include "GameMap.h"
#include "TileLayer.h"
#include <map>
#include <string>

class MapParser{
    public:
        inline static MapParser* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
        }

        bool Load();
        void Clean();

        inline GameMap* GetMaps();

    private:
        bool Parse(std::string id, std::string source);
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer);

    private:
        MapParser(){}
        static MapParser* s_Instance;
        std::map<std::string, GameMap*> m_MapDict;
};

#endif