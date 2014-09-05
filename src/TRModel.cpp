//
//  TRModel.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/2/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "TRModel.h"
#include "logger.h"

TRModel::TRModel(){
    
    
    m_model = _SharedPtr<TerosObject>(new TerosObject);
    m_mesh = _SharedPtr<MeshModel>(new MeshModel);
    
    m_position.set(m_posx, m_posy, m_posz, 1.0f);
    m_velocity.set(-1.0, 0.0, 0.0, 0.0f);

}


void TRModel::constructFromMesh(_SharedPtr<MeshModel> source, int size){
    
    //logger logmaker("log.txt", 0);
    
    if(size < 1)
        size = 1;
    
    
    for(int x = 0; x < source->m_indices.size(); x++){
        
        
        _SharedPtr<TerosPolygon> l_triangle = _SharedPtr<TerosPolygon>(new TerosPolygon);
        l_triangle->modp(0, source->m_points.at(source->m_indices.at(x).x()).x()*size,
                         source->m_points.at(source->m_indices.at(x).x()).y()*size,
                         source->m_points.at(source->m_indices.at(x).x()).z()*size);
        
        l_triangle->modp(1, source->m_points.at(source->m_indices.at(x).y()).x()*size,
                         source->m_points.at(source->m_indices.at(x).y()).y()*size,
                         source->m_points.at(source->m_indices.at(x).y()).z()*size);
        
        l_triangle->modp(2, source->m_points.at(source->m_indices.at(x).z()).x()*size,
                         source->m_points.at(source->m_indices.at(x).z()).y()*size,
                         source->m_points.at(source->m_indices.at(x).z()).z()*size);
        

        l_triangle->setIndex(x);
        
        /*
        if(x == 14 || x == 268)
            l_triangle->setfill('F');
        else if(x%2)
            l_triangle->setfill('#');
        else
            l_triangle->setfill('@');
        */

        m_polygons.push_back(l_triangle);
        
    }
    
    for(int x = 0; x < source->m_colors.size(); x++){
        
        int index = source->m_colors.at(x).index;
        
        if(index > -1 && index < m_polygons.size()){
            
                if(m_polygons.at(index)->getIndex() == index){
                    
                    _SharedPtr<TerosPolygon> l_triangle = m_polygons.at(index);
                    
                    l_triangle->setAttr(source->m_colors.at(x).s,
                                        source->m_colors.at(x).fg,
                                        source->m_colors.at(x).bg,
                                        source->m_colors.at(x).attr);
                    
                    l_triangle->setfill(source->m_colors.at(x).s);
                    
                }
        }
        
        
    }
     
    
    for(int x = 0; x < m_polygons.size(); x++){
        m_model->addside(m_polygons.at(x).get());
    }

    
}



