/********************************************************************
 *  Copyright (C) 2016 by Federico Marulli and Alfonso Veropalumbo  *
 *  federico.marulli3@unibo.it                                      *
 *                                                                  *
 *  This program is free software; you can redistribute it and/or   * 
 *  modify it under the terms of the GNU General Public License as  *
 *  published by the Free Software Foundation; either version 2 of  *
 *  the License, or (at your option) any later version.             *
 *                                                                  *
 *  This program is distributed in the hope that it will be useful, *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of  *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   *
 *  GNU General Public License for more details.                    *
 *                                                                  *
 *  You should have received a copy of the GNU General Public       *
 *  License along with this program; if not, write to the Free      *
 *  Software Foundation, Inc.,                                      *
 *  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.       *
 ********************************************************************/

/**
 *  @file
 *  Modelling/Cosmology/ModelFunction_Cosmology.cpp
 *
 *  @brief Global functions to model cosmological measurements
 *
 *  This file contains the implementation of the functions used to
 *  model cosmological measurements
 *
 *  @authors Federico Marulli, Alfonso Veropalumbo
 *
 *  @authors federico.marulli3@unbo.it, alfonso.veropalumbo@unibo.it
 */

#include "ModelFunction_Cosmology.h"

using namespace cosmobl;


// ============================================================================================


double cosmobl::modelling::cosmology::cosmological_measurements(const double redshift, const string data_type, const cosmobl::cosmology::Cosmology cosmology)
{
  if(data_type == "DV")
    return cosmology.D_V(redshift);
  
  else if (data_type == "DV/rs")
    return cosmology.D_V(redshift)/cosmology.rs();
  
  else if (data_type == "rs/DV")
    return cosmology.rs()/cosmology.D_V(redshift);
  
  else if(data_type == "DA")
    return cosmology.D_A(redshift);
  
  else if (data_type == "DA/rs")
    return cosmology.D_A(redshift)/cosmology.rs();
  
  else if (data_type == "rs/DA")
    return cosmology.rs()/cosmology.D_A(redshift);

  else if(data_type == "DM")
    return cosmology.D_M(redshift);
  
  else if (data_type == "DM/rs")
    return cosmology.D_M(redshift)/cosmology.rs();
  
  else if (data_type == "rs/DM")
    return cosmology.rs()/cosmology.D_M(redshift);
  
  else if(data_type == "HH")
    return cosmology.HH(redshift);

  else if (data_type == "HH*rs")
    return cosmology.HH(redshift)*cosmology.rs();

  else if(data_type == "DH")
    return cosmobl::par::cc/cosmology.HH(redshift);

  else if (data_type == "DH/rs")
    return cosmobl::par::cc/cosmology.HH(redshift)/cosmology.rs();

  else if (data_type == "rs/DH")
    return cosmology.rs()/(cosmobl::par::cc/cosmology.HH(redshift));

  else if (data_type == "DL")
    return cosmology.D_L(redshift);
  else
    ErrorCBL("Error in cosmological_measurements, no such type of measurement");

  return 0;
}


// ============================================================================================


vector<double> cosmobl::modelling::cosmology::cosmological_measurements_model(const vector<double> redshift, const shared_ptr<void> inputs, vector<double> &parameter)
{
  // structure contaning the required input data
  shared_ptr<STR_data_model_cosmology> pp = static_pointer_cast<STR_data_model_cosmology>(inputs);

  // redefine the cosmology
  cosmobl::cosmology::Cosmology cosmo = *pp->cosmology;

  // input likelihood parameters

  // set the cosmological parameters used to compute the dark matter
  // two-point correlation function in real space
  for (size_t i=0; i<pp->Cpar.size(); ++i)
    cosmo.set_parameter(pp->Cpar[i], parameter[i]);

  vector<double> output;

  for(size_t i=0; i<redshift.size(); i++)
    output.push_back(cosmobl::modelling::cosmology::cosmological_measurements(redshift[i], pp->data_type[i], cosmo));

  return output;
}


// ============================================================================================


vector<double> cosmobl::modelling::cosmology::cosmological_measurements_model_CMB_DistancePrior(const vector<double> redshift, const shared_ptr<void> inputs, vector<double> &parameter)
{
  // structure contaning the required input data
  shared_ptr<STR_data_model_cosmology> pp = static_pointer_cast<STR_data_model_cosmology>(inputs);

  // redefine the cosmology
  cosmobl::cosmology::Cosmology cosmo = *pp->cosmology;

  // input likelihood parameters

  // set the cosmological parameters used to compute the dark matter
  // two-point correlation function in real space
  for (size_t i=0; i<pp->Cpar.size(); ++i)
    cosmo.set_parameter(pp->Cpar[i], parameter[i]);

  vector<double> output;

  for(size_t i=0; i<redshift.size()-pp->distance_prior->dataset()->ndata(); i++)
    output.push_back(cosmobl::modelling::cosmology::cosmological_measurements(redshift[i], pp->data_type[i], cosmo));

  vector<double> mm = pp->distance_prior->model(cosmo);
  for(size_t i=0; i<mm.size(); i++)
    output.push_back(mm[i]);

  return output;
}
