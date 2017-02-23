#include "Map.h"

Map::Map(coord lc, coord uc){

    // Check coordinate
    if( !(lc.Less(uc)) ){
        LOG("Map::Map Lower coordinates must be larger than upper coordinates");
        exit(EXIT_FAILURE);
    }

    this->lc = lc;
    this->uc = uc;
    this->dx = this->uc.x - this->lc.x;
    this->dy = this->uc.y - this->lc.y;
    this->dz = this->uc.z - this->lc.z;

}

// Add an obstacle to the map
bool Map::AddObstacle(coord lc, coord uc){

    // Check coordinate
    if( !(lc.Less(uc)) ){
         LOG("Map::addObstacle Lower coordinates must be larger than upper coordinates");
         return false;
    }


    // Check if box is in map space
    if( !( this->InMapSpace(lc) && this->InMapSpace(uc)) ){
        LOG("Map::addObstacle Obstacle falls outside map space");
        return false;
    }

    this->obstacles.push_back(tuple<coord,coord>(lc,uc));
    return true;

}

// Check if there's an obstacle in c
bool Map::ObstacleIn(coord c){

    vector< tuple<coord,coord> >::iterator it;
    for(it=this->obstacles.begin() ; it < this->obstacles.end(); it++ ) {

        // check if c is in an obstacle
        if( c.In( get<0>(*it), get<1>(*it) ) ){
            return true;
        }
    }
    return false;
}

// Convert coordinate to index
int Map::Coord2Idx(coord c){

    // check if c is in map space
    if( !(this->InMapSpace(c)) ){
        return -1;
    }

    // shift space in (0,0,0)
    c.x = c.x - this->lc.x;
    c.y = c.y - this->lc.y;
    c.z = c.z - this->lc.z;
    return c.x + c.y*this->dx + c.z*(this->dx*this->dy);
}

// Check if coordinate is in map space
bool Map::InMapSpace(coord c){
    return c.In(this->lc,this->uc);
}


