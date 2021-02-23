/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <vector>
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     MosaicCanvas* ans = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     vector<Point<3>> tiles; // used for constructing tree
     int rows = theSource.getRows();
     int columns = theSource.getColumns();
     std::map<Point<3>, TileImage*> collection; // to find XYZ that correspond to TileImage
     //assign map values and making vector of XYZPoints
     for (unsigned int k = 0; k < theTiles.size(); k++) {
       Point<3> XYZPoint = convertToXYZ(theTiles[k].getAverageColor());
       tiles.push_back(XYZPoint);
       //std::cout << tiles.size() << std::endl;
       std::pair<Point<3>, TileImage*> insertThis(XYZPoint, &theTiles[k]);
       collection.insert(insertThis);
     }
     //std::cout << collection.size() << std::endl;
     KDTree<3> kdTree(tiles);
     //adding in tiles
     for (int k = 0; k < rows; k++) {
       for (int j = 0; j < columns; j++) {
         Point<3> target = convertToXYZ(theSource.getRegionColor(k, j)); //XYZ of point (k, j)
         //std::cout << "Target" << target << std::endl;
         Point<3> closestNeighbor = kdTree.findNearestNeighbor(target); //most relavent point to that target
         //std::cout << "closestNeighbor" << closestNeighbor << std::endl;
         TileImage* tileAt = collection[closestNeighbor]; //get that point from the map
         ans->setTile(k, j, tileAt); //set it
       }
     }
    return ans;
}
