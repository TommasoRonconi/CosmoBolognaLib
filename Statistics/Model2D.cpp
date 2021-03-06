/********************************************************************
 *  Copyright (C) 2014 by Federico Marulli and Alfonso Veropalumbo  *
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
 *  @file Statistics/Model2D.cpp
 *
 *  @brief Methods of the class Model2D
 *
 *  This file contains the implementation of the methods of the class
 *  Model2D
 *
 *  @authors Federico Marulli, Alfonso Veropalumbo
 *
 *  @authors federico.marulli3@unbo.it, alfonso.veropalumbo@unibo.it
 */

#include "Model2D.h"

using namespace cosmobl;


// ======================================================================================


void cosmobl::statistics::Model2D::set_model (const model_function_2D model)
{
  m_function = [model](vector<vector<double>> xx, shared_ptr<void> fixed_parameters, vector<double> &free_parameters) 
    {
      return model(xx[0], xx[1], fixed_parameters, free_parameters);
    };
}


// ======================================================================================


void cosmobl::statistics::Model2D::write_model (const string output_dir, const string output_file, const vector<double> xx, const vector<double> yy, vector<double> &parameter) const
{
  string mkdir = "mkdir -p "+output_dir; if (system(mkdir.c_str())) {}

  string file_out = output_dir+output_file;
  ofstream fout(file_out.c_str()); checkIO(fout, file_out);

  vector<vector<double>> model = this->operator()(xx, yy, parameter);

  for (size_t i=0; i<xx.size(); i++)
    for (size_t j=0; j<yy.size(); j++)
      fout << xx[i] << " " << yy[j] << " " << model[i][j] << endl;

  fout.clear(); fout.close();
  coutCBL << "I wrote the file: " << output_dir+file_out << endl;
}

