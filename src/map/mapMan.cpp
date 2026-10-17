#include "map/mapMan.hpp"

mapMan::mapMan(){
    cuteMap = cute_tiled_load_map_from_file("data/map.json", nullptr);

    tileset = LoadTexture("data/tileset.png");

    cuteTS = cuteMap->tilesets;

    tileCount = {tileset.width/TILESIZE, tileset.height/TILESIZE};
}

mapMan::~mapMan(){
    UnloadTexture(tileset);
    cute_tiled_free_map(cuteMap);
}

void mapMan::draw(){
    for(cute_tiled_layer_t* layer = cuteMap->layers; layer; layer = layer->next){
        if (!layer->data) continue;
        if (!layer->type.ptr || !TextIsEqual(layer->type.ptr, "tilelayer")) continue;
        // -------------------------------------------------------------------
        for (int y = 0; y<layer->height; y++){
            for (int x = 0; x<layer->width; x++){
                int indx = y * layer->width + x;
                int data = layer->data[indx];
                
                if (data==0) continue;

                data = cute_tiled_unset_flags(data);

                if (!cuteTS || tileCount.x <= 0 || tileCount.y <= 0) {
                    TraceLog(LOG_ERROR, "Tileset bilgileri gecersiz!");
                    return;
                }

                // Çizim
                int id = data - 1;
                Vector2i tilePos = {id % (int)tileCount.x, id / (int)tileCount.y};

                DrawTexturePro(tileset, {tilePos.x*TILESIZE, tilePos.y*TILESIZE, TILESIZE, TILESIZE}, 
                        {x*TILESIZE, y*TILESIZE, TILESIZE, TILESIZE}, {0,0}, 0.f, WHITE);
            }
        }
    }
}

TileData mapMan::getTileByPos(Vector2 mousePos){
    Vector2i tilePos = {(int)(mousePos.x)/(int)(TILESIZE), (int)(mousePos.y)/(int)(TILESIZE)};
    Vector2i tilesSize = {cuteMap->width, cuteMap->height};

    TileData out = {tilePos, 0, false};

    if(tilePos.x>tilesSize.x || tilePos.y>tilesSize.y) return out;

    // -------------------------------------------------------------------
    for (cute_tiled_layer_t* layer = cuteMap->layers; layer; layer = layer->next) {
        if (!layer->data) continue;
        if (tilePos.x < 0 || tilePos.y < 0 || tilePos.x >= layer->width || tilePos.y >= layer->height) continue;

        int indx = tilePos.y * layer->width + tilePos.x;
        int data = layer->data[indx];

        if (data==0) continue;

        data = cute_tiled_unset_flags(data);
        int id = data - 1;
        out.type = id;
        out.trueVal = true;
        
        return out; 
    }
    return out;
}

bool mapMan::isInCollionWithID(Vector2 objPos, Vector2 objSize, int selectedID){
    Rectangle ObjRec = {objPos.x, objPos.y, objSize.x, objSize.y};
    Vector2i StartPos = {
        ((int)objPos.x/(int)TILESIZE), 
        ((int)objPos.y/(int)TILESIZE)};
    Vector2i EndPos = {
        ((int)(objPos.x+objSize.x)/(int)TILESIZE), 
        ((int)(objPos.y+objSize.y)/(int)TILESIZE)};

    cute_tiled_layer_t* layer =  cuteMap->layers;

    if (!layer || !layer->data)
        return false;
    // --------------------------------------------------------------
    int size = 2;
    for (int y = StartPos.y-size; y <= EndPos.y+size; y++) {
        for (int x = StartPos.x-size; x <= EndPos.x+size; x++) {

            //! Hata ayıklama
            if (x < 0 || y < 0 || x >= layer->width || y >= layer->height) continue;
            
            int indx = y * layer->width + x;
            int data = layer->data[indx];

            Rectangle tileRec = {x*TILESIZE, y*TILESIZE, TILESIZE, TILESIZE};


            if(data==selectedID && CheckCollisionRecs(ObjRec, tileRec)){
                //TraceLog(LOG_INFO, "selectedID=%d, data=%d, x=%d, y=%d", selectedID, data, x, y);
                //TraceLog(LOG_INFO, "%i Tile: {%f, %f} TileTilePos: {%i, %i}",data,  tileRec.x, tileRec.y ,x, y);
                return true;
                
            }
        }
    }

    return false;
}