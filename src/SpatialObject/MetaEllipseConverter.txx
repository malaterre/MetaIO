/*=========================================================================

  Program:   itkUNC
  Module:    MetaEllipseConverter.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$
  Author:    Julien Jomier (julien@jomier.com)

  Copyright (c) 2002 CADDLab @ UNC. All rights reserved.
  See itkUNCCopyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __MetaEllipseConverter__txx
#define __MetaEllipseConverter__txx

#include "MetaEllipseConverter.h"

/** Constructor */ 
template <unsigned int NDimensions>                                          
MetaEllipseConverter<NDimensions>
::MetaEllipseConverter()
{
  
}


/** Convert a metaEllipse into an ellipse SpatialObject  */
template <unsigned int NDimensions>       
typename MetaEllipseConverter<NDimensions>::SpatialObjectPointer
MetaEllipseConverter<NDimensions>
::MetaEllipseToEllipseSpatialObject(MetaEllipse * ellipse)
{ 
  SpatialObjectPointer spatialObject = SpatialObjectType::New();
  typename SpatialObjectType::ArrayType radius;
  for(unsigned int i=0;i<NDimensions;i++)
  {
    radius[i]=ellipse->Radius()[i];
  }
  spatialObject->SetRadius(radius);
  spatialObject->GetProperty()->SetName(ellipse->Name());
  spatialObject->SetId(ellipse->ID());
  spatialObject->SetParentId(ellipse->ParentID());
  return spatialObject;
}

/** Convert an ellipse SpatialObject into a metaEllipse */
template <unsigned int NDimensions>       
MetaEllipse*
MetaEllipseConverter<NDimensions>
::EllipseSpatialObjectToMetaEllipse(SpatialObjectType * spatialObject)
{ 
  MetaEllipse* ellipse = new MetaEllipse(NDimensions);

  float* radius = new float[NDimensions];
  for(unsigned int i=0;i<NDimensions;i++)
  {
    radius[i] = spatialObject->GetRadius()[i];
  }

  if(spatialObject->GetParent())
  {
    ellipse->ParentID(spatialObject->GetParent()->GetId());
  }
  ellipse->Radius(radius);
  ellipse->ID(spatialObject->GetId());
  return ellipse;
}


/** Read a meta file give the type */
template <unsigned int NDimensions>       
typename MetaEllipseConverter<NDimensions>::SpatialObjectPointer
MetaEllipseConverter<NDimensions>
::ReadMeta(const char* name)
{
  SpatialObjectPointer spatialObject;
  MetaEllipse* ellipse = new MetaEllipse();
  ellipse->Read(name);
  spatialObject = MetaEllipseToEllipseSpatialObject(ellipse);

  return spatialObject;
}


/** Write a meta ellipse file */
template <unsigned int NDimensions>
bool
MetaEllipseConverter<NDimensions>
::WriteMeta(SpatialObjectType* spatialObject,const char* name)
{
  MetaEllipse* ellipse = EllipseSpatialObjectToMetaEllipse(spatialObject);
  ellipse->Write(name);
  return true;
}

#endif
