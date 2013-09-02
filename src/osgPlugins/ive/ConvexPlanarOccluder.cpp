/**********************************************************************
 *
 *    FILE:            ConvexPlanarOccluder.cpp
 *
 *    DESCRIPTION:    Read/Write osg::ConvexPlanarOccluder in binary format to disk.
 *
 *    CREATED BY:        Auto generated by iveGenerator
 *                    and later modified by Rune Schmidt Jensen.
 *
 *    HISTORY:        Created 23.4.2003
 *
 *    Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "Object.h"
#include "ConvexPlanarOccluder.h"
#include "ConvexPlanarPolygon.h"

using namespace ive;

void ConvexPlanarOccluder::write(DataOutputStream* out){
    // Write ConvexPlanarOccluder's identification.
    out->writeInt(IVECONVEXPLANAROCCLUDER);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object*  obj = dynamic_cast<osg::Object*>(this);
    if(obj){
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("ConvexPlanarOccluder::write(): Could not cast this osg::ConvexPlanarOccluder to an osg::Object.");
    // Write ConvexPlanarOccluder's properties.

    // Write planar polygon occluder.
    ((ive::ConvexPlanarPolygon*)(&getOccluder()))->write(out);

    // Write hole list.
    HoleList holeList = getHoleList();
    int size = holeList.size();
    out->writeInt(size);
    for(int i=0; i<size; i++){
        ((ive::ConvexPlanarPolygon*)(&holeList[i]))->write(out);
    }
}

void ConvexPlanarOccluder::read(DataInputStream* in){
    // Peek on ConvexPlanarOccluder's identification.
    int id = in->peekInt();
    if(id == IVECONVEXPLANAROCCLUDER){
        // Read ConvexPlanarOccluder's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object*  obj = dynamic_cast<osg::Object*>(this);
        if(obj){
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("ConvexPlanarOccluder::read(): Could not cast this osg::ConvexPlanarOccluder to an osg::Object.");
        // Read ConvexPlanarOccluder's properties

        // Read planar polygon occluder.
        osg::ConvexPlanarPolygon* cpp = &getOccluder();
        ((ive::ConvexPlanarPolygon*)(cpp))->read(in);

        // Read hole list.
        int size = in->readInt();
        for(int i=0; i<size; i++){
            osg::ConvexPlanarPolygon* cpp = new osg::ConvexPlanarPolygon();
            ((ive::ConvexPlanarPolygon*)(cpp))->read(in);
            addHole(*cpp);
        }

    }
    else{
        in_THROW_EXCEPTION("ConvexPlanarOccluder::read(): Expected ConvexPlanarOccluder identification.");
    }
}