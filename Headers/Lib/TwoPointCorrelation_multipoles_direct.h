/********************************************************************
 *  Copyright (C) 2010 by Federico Marulli and Alfonso Veropalumbo  *
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
 *  @file Headers/Lib/TwoPointCorrelation_multipoles_direct.h
 *
 *  @brief The class TwoPointCorrelation_multipoles_direct
 *
 *  This file defines the interface of the class
 *  TwoPointCorrelation_multipoles_direct, used to measure the first
 *  three non-null multipole moments of the two-point correlation
 *  function, directly from the pair counts
 *
 *  @authors Federico Marulli, Alfonso Veropalumbo
 *
 *  @authors federico.marulli3@unbo.it, alfonso.veropalumbo@unibo.it
 */

#ifndef __TWOPOINTMULTD__
#define __TWOPOINTMULTD__


#include "TwoPointCorrelation1D_monopole.h"


// ===================================================================================================


namespace cosmobl {
  
  namespace measure {

    namespace twopt {

      /**
       *  @class TwoPointCorrelation_multipoles_direct
       *  TwoPointCorrelation_multipoles_direct.h
       *  "Headers/Lib/TwoPointCorrelation_multipoles_direct.h"
       *
       *  @brief The class TwoPointCorrelation_multipoles_direct
       *
       *  This class is used to handle objects of type <EM>
       *  TwoPointCorrelation_multipoles_direct </EM>. It is used to
       *  measure the first three non-null multipole moments of the
       *  two-point correlation function, i.e. the monopole, the
       *  quadrupole and the exadecupole \f$\xi_l(r) = (2l+1)
       *  \int_{\mu_{min}}^{\mu_{max}} \xi(s,\mu) L_l(\mu) d\mu\f$,
       *  with \f$l=0,2,4\f$.
       *
       *  This class uses the so-called <EM> direct </EM> method: each
       *  pair is weighted with the Legendre polynomial of the
       *  corresponding multipole, computed at the cosine of the
       *  angular separation between the objects
       *  
       *  The monopole estimated with the <EM> direct </EM> method can
       *  be obtained with the class TwoPointCorrelation_monopole
       */
      class TwoPointCorrelation_multipoles_direct : public TwoPointCorrelation1D_monopole {

        protected:

          /**
           *  @brief write the number of pairs
           *  @param PP pointer to an object of class Pair
           *  @param dir output directory
           *  @param file output file
           *  @return none
           */
          void write_pairs (const shared_ptr<pairs::Pair> PP, const string dir, const string file) const override;

          /**
           *  @brief read the number of pairs
           *  @param [out] PP pointer to an object of class Pair
           *  @param [in] dir vector of input directories
           *  @param [in] file input file
           *  @return none
           */
          void read_pairs (shared_ptr<pairs::Pair> PP, const vector<string> dir, const string file) const override;

          /**
           *  @brief write the number of pairs
           *  @param PP pointer to a vector of objects of class Pair
           *  @param dir output directory
           *  @param file output file
           *  @return none
           */
          void write_pairs (const vector<shared_ptr<pairs::Pair>> PP, const string dir, const string file) const override;

          /**
           *  @brief read the number of pairs
           *  @param [out] PP pointer to a vector of objects of class Pair
           *  @param [in] dir vector of input directories
           *  @param [in] file input file
           *  @return none
           */
          void read_pairs (vector<shared_ptr<pairs::Pair>> PP, const vector<string> dir, const string file) const override;

          /**
           *  @brief get a dataset containing the two-point correlation
           *  function measured with the natural estimator, and its
           *  Poisson errors
           *  
           *  @param dd pointer to an object of type Pair containing the
           *  data-data pairs
           *
           *  @param rr pointer to an object of type Pair containing the
           *  random-random pairs
           *
           *  @param nData number of objects in the data catalogue
           *
           *  @param nData_weighted weighted number of objects in the
           *  data catalogue
           *
           *  @param nRandom number of objects in the random catalogue
           *
           *  @param nRandom_weighted weighted number of objects in the
           *  random catalogue
           *
           *  @return pointer to an object of type Data
           */
          shared_ptr<data::Data> correlation_NaturalEstimator (const shared_ptr<pairs::Pair> dd, const shared_ptr<pairs::Pair> rr, const int nData=0, const double nData_weighted=0., const int nRandom=0, const double nRandom_weighted=0.) override;

          /**
           *  @brief get a dataset containing the two-point correlation
           *  function measured with the Landy-Szalay estimator, and its
           *  Poisson errors
           *  
           *  @param dd pointer to an object of type Pair containing the
           *  data-data pairs
           *
           *  @param rr pointer to an object of type Pair containing the
           *  random-random pairs
           *
           *  @param dr pointer to an object of type Pair containing the
           *  data-random pairs
           *
           *  @param nData number of objects in the data catalogue
           *
           *  @param nData_weighted weighted number of objects in the
           *  data catalogue
           *
           *  @param nRandom number of objects in the random catalogue
           *
           *  @param nRandom_weighted weighted number of objects in the
           *  random catalogue
           *
           *  @return pointer to an object of type Data
           */
          shared_ptr<data::Data> correlation_LandySzalayEstimator (const shared_ptr<pairs::Pair> dd, const shared_ptr<pairs::Pair> rr, const shared_ptr<pairs::Pair> dr, const int nData=0, const double nData_weighted=0., const int nRandom=0, const double nRandom_weighted=0.) override;

	/**
	 *  @brief measure the jackknife resampling of the two-point
	 *  correlation function, &xi;(r)
	 *
	 *  @param dd vector of data-data pairs, divided per regions
	 *
	 *  @param rr vector of random-random pairs, divided per regions
	 *
	 *  @return pointer to a vector of Data object
	 */
	vector<shared_ptr<data::Data>> XiJackknife (const vector<shared_ptr<pairs::Pair>> dd, const vector<shared_ptr<pairs::Pair>> rr) override;

	/**
	 *  @brief measure the jackknife resampling of the two-point
	 *  correlation function, &xi;(r)
	 *
	 *  @param dd vector of data-data pairs, divided per regions
	 *
	 *  @param rr vector of random-random pairs, divided per regions
	 *
	 *  @param dr vector of data-random pairs, divided per regions
	 *
	 *  @return pointer to a vector of Data object
	 */
	vector<shared_ptr<data::Data>> XiJackknife (const vector<shared_ptr<pairs::Pair>> dd, const vector<shared_ptr<pairs::Pair>> rr, const vector<shared_ptr<pairs::Pair>> dr) override;

        /**
         *  @brief measure the bootstrap resampling of the two-point
         *  correlation function, &xi;(r)
         *
         *  @param nMocks number of resampling
         *
         *  @param dd vector of data-data pairs, divided per regions
         *
         *  @param rr vector of random-random pairs, divided per
         *  regions
         *
         *  @param seed the seed for random number generation
         *
         *  @return pointer to a vector of Data object
         */
        vector<shared_ptr<data::Data>> XiBootstrap (const int nMocks, const vector<shared_ptr<pairs::Pair>> dd, const vector<shared_ptr<pairs::Pair>> rr, const int seed=3213) override;

        /**
         *  @brief measure the bootstrap resampling of the two-point
         *  correlation function, &xi;(r)
         *
         *  @param nMocks number of resampling
         *
         *  @param dd vector of data-data pairs, divided per regions
         *
         *  @param rr vector of random-random pairs, divided per
         *  regions
         *
         *  @param dr vector of data-random pairs, divided per regions  
         *
         *  @param seed the seed for random number generation
         *
         *  @return pointer to a vector of Data object
         */
        vector<shared_ptr<data::Data>> XiBootstrap (const int nMocks, const vector<shared_ptr<pairs::Pair>> dd, const vector<shared_ptr<pairs::Pair>> rr, const vector<shared_ptr<pairs::Pair>> dr, const int seed=3213) override;

        public:

          /**
           *  @name Constructors/destructors
           */
          ///@{

          /**
           *  @brief default constructor
           *  @return object of class TwoPointCorrelation_multipoles_direct
           */
          TwoPointCorrelation_multipoles_direct () { m_twoPType = _multipoles_direct_; }

          /**
           *  @brief constructor
	   *
           *  @param data object of class Catalogue containing the
           *  input catalogue
	   *
           *  @param random of class Catalogue containing the random
           *  data catalogue
	   *
           *  @param binType binning type
	   *
           *  @param rMin minimum separation used to count the pairs
           *
	   *  @param rMax maximum separation used to count the pairs
           *
	   *  @param nbins number of bins
	   *
	   *  @param shift shift parameter, i.e. the radial shift is
           *  binSize*shift
	   *
           *  @param angularUnits angular units
	   *
           *  @param angularWeight angular weight function
	   *
           *  @param compute_extra_info true &rarr; compute extra
           *  information related to the pairs, such as the mean pair
           *  separation and redshift
	   *
           *  @param random_dilution_fraction fraction between the
           *  number of objects in the diluted and original random
           *  samples, used to improve performances in random-random
           *  pair counts
	   *
	   *  @return object of class
	   *  TwoPointCorrelation_multipoles_direct
           */
          TwoPointCorrelation_multipoles_direct (const catalogue::Catalogue data, const catalogue::Catalogue random, const binType binType, const double rMin, const double rMax, const int nbins, const double shift, const CoordUnits angularUnits=_radians_, function<double(double)> angularWeight=nullptr, const bool compute_extra_info=false, const double random_dilution_fraction=1.) 
	    : TwoPointCorrelation(data, random, compute_extra_info, random_dilution_fraction), TwoPointCorrelation1D(data, random, compute_extra_info, random_dilution_fraction)
	  { m_twoPType = _multipoles_direct_; set_parameters(binType, rMin, rMax, nbins, shift, angularUnits, angularWeight, compute_extra_info); }

          /**
           *  @brief constructor
	   *
           *  @param data object of class Catalogue containing the
           *  input catalogue
	   *
           *  @param random of class Catalogue containing the random
           *  data catalogue
	   *
           *  @param binType binning type
	   *
           *  @param rMin minimum separation used to count the pairs
	   *
           *  @param rMax maximum separation used to count the pairs
	   *
           *  @param binSize the bin size
	   *
           *  @param shift shift parameter, i.e. the radial shift is
           *  binSize*shift
	   *
           *  @param angularUnits angular units
	   *
           *  @param angularWeight angular weight function
	   *
           *  @param compute_extra_info true &rarr; compute extra
           *  information related to the pairs, such as the mean pair
           *  separation and redshift
	   *
           *  @param random_dilution_fraction fraction between the
           *  number of objects in the diluted and original random
           *  samples, used to improve performances in random-random
           *  pair counts
	   *
           *  @return object of class TwoPointCorrelation_monopole
           */
          TwoPointCorrelation_multipoles_direct (const catalogue::Catalogue data, const catalogue::Catalogue random, const binType binType, const double rMin, const double rMax, const double binSize, const double shift, const CoordUnits angularUnits=_radians_, function<double(double)> angularWeight=nullptr, const bool compute_extra_info=false, const double random_dilution_fraction=1.)
            : TwoPointCorrelation(data, random, compute_extra_info, random_dilution_fraction), TwoPointCorrelation1D(data, random, compute_extra_info, random_dilution_fraction)
	  { m_twoPType = _multipoles_direct_; set_parameters(binType, rMin, rMax, binSize, shift, angularUnits, angularWeight, compute_extra_info); }

          /**
           *  @brief default destructor
           *  @return none
           */
          ~TwoPointCorrelation_multipoles_direct () = default;

          ///@}

	  /**
	   *  @name Member functions to 
	   */
	  ///@{

	  /**
	   *  @brief get the x coordinates
	   *  @return the x coordinates
	   */
	  vector<double> xx () const  override;

	  /**
	   *  @brief get the the binned correlation function 
	   *  @return the binned correlation function 
	   */
	  vector<double> xi1D () const
	  { cosmobl::ErrorCBL("Error in xi1D() of TwoPointCorrelation_multipoles_direct.h!"); vector<double> vv; return vv; }

	  /**
	   *  @brief get the error on the binned correlation function
	   *  function
	   *  @return the error on the binned correlation function
	   *  function
	   */
	  vector<double> error1D () const
	  { cosmobl::ErrorCBL("Error in error1D() of TwoPointCorrelation_multipoles_direct.h!"); vector<double> vv; return vv; }

	  /**
	   *  @brief get the monopole of the polar xi
	   *  @return the xiMonopole
	   */
	  vector<double> xiMonopole () const override;

	  /**
	   *  @brief get the error on the monopole of the polar xi
	   *  @return the error on the Monopole
	   */
	  vector<double> errorMonopole () const override;

	  /**
	   *  @brief get the quadrupole of the polar xi
	   *  @return the Quadrupole
	   */
	  vector<double> xiQuadrupole () const override;

	  /**
	   *  @brief get the error on the quadrupole of the polar xi
	   *  @return the error on the Quadrupole
	   */
	  vector<double> errorQuadrupole () const override;

	  /**
	   *  @brief get the hexadecapole of the polar xi
	   *  @return the Hexadecapole
	   */
	  vector<double> xiHexadecapole () const override;

	  /**
	   *  @brief get the error on the hexadecapole of the polar xi
	   *  @return the error on Hexadecapole
	   */
	  vector<double> errorHexadecapole () const override;
	  
	  ///@}

          /**
           *  @name Member functions to set the binning parameters
           */
          ///@{

          /**
           *  @brief set the binning parameters
           *  @param binType binning type
           *  @param rMin minimum separation used to count the pairs
           *  @param rMax maximum separation used to count the pairs
           *  @param nbins number of bins
           *  @param shift shift parameter, i.e. the radial shift is
           *  binSize*shift
           *  @param angularUnits angular units
           *  @param angularWeight angular weight function
           *  @param compute_extra_info true &rarr; compute extra
           *  information related to the pairs, such as the mean pair
           *  separation and redshift
           *  @return none
           */
          void set_parameters (const binType binType, const double rMin, const double rMax, const int nbins, const double shift, const CoordUnits angularUnits=_radians_, function<double(double)> angularWeight=nullptr, const bool compute_extra_info=false);

          /**
           *  @brief set the binning parameters
           *  @param binType binning type
           *  @param rMin minimum separation used to count the pairs
           *  @param rMax maximum separation used to count the pairs
           *  @param binSize the bin size
           *  @param shift shift parameter, i.e. the radial shift is
           *  binSize*shift
           *  @param angularUnits angular units
           *  @param angularWeight angular weight function
           *  @param compute_extra_info true &rarr; compute extra
           *  information related to the pairs, such as the mean pair
           *  separation and redshift
           *  @return none
           */
          void set_parameters (const binType binType, const double rMin, const double rMax, const double binSize, const double shift, const CoordUnits angularUnits=_radians_, function<double(double)> angularWeight=nullptr, const bool compute_extra_info=false);

          ///@}

          /**
           *  @name Input/Output methods
           */
          ///@{

	  /**
	   *  @brief read the multipoles of the two-point correlation
	   *  function
	   *  @param dir input directory
	   *  @param file input file
	   *  @return none
	   */
	  void read (const string dir, const string file) override
	  { (void)dir; (void)file; ErrorCBL("Error in TwoPointCorrelation_multipoles::read of TwoPointCorrelation_multipoles.h: work in progress!", glob::ExitCode::_workInProgress_); }

	  /**
	   *  @brief write the multipoles of the two-point correlation
	   *  function
           *  @param dir output directory
           *  @param file output file
           *  @param rank cpu index (for MPI usage)
           *  @return none
           */
	  void write (const string dir=par::defaultString, const string file=par::defaultString, const int rank=0) const override;

	  /**
	   *  @brief return a data object with extra info
	   *  
	   *  @param dd pointer to an object of type Pair containing the
	   *  data-data pairs
	   *  @param rad vector containing the binned scales
	   *  @param xi vector containing the binned two-point correlation
	   *  function
	   *  @param error vector containing the errors
	   *
	   *  @return pointer to an object of type Data
	   */
	  shared_ptr<data::Data> data_with_extra_info (const shared_ptr<pairs::Pair> dd, const vector<double> rad, const vector<double> xi, const vector<double> error) const;

          ///@}

      };


    }

  }
}

#endif
