#ifndef CBALGOPROHIBITALLTRACKS_CXX
#define CBALGOPROHIBITALLTRACKS_CXX

#include "CBAlgoProhibitAllTracks.hh"

namespace cmtool {

  //-------------------------------------------------------
  CBAlgoProhibitAllTracks::CBAlgoProhibitAllTracks() : CBoolAlgoBase()
  //-------------------------------------------------------
  {
    SetMinEP(.990000);
  }

  //-----------------------------
  void CBAlgoProhibitAllTracks::Reset()
  //-----------------------------
  {

  }

  //------------------------------------------------------------------------------------------
  //void CBAlgoProhibitAllTracks::EventBegin(const std::vector<cluster::ClusterParamsAlgNew> &clusters)
  //------------------------------------------------------------------------------------------
  //{
  //
  //}

  //-------------------------------
  //void CBAlgoProhibitAllTracks::EventEnd()
  //-------------------------------
  //{
  //
  //}

  //-----------------------------------------------------------------------------------------------
  //void CBAlgoProhibitAllTracks::IterationBegin(const std::vector<cluster::ClusterParamsAlgNew> &clusters)
  //-----------------------------------------------------------------------------------------------
  //{
  //
  //}

  //------------------------------------
  //void CBAlgoProhibitAllTracks::IterationEnd()
  //------------------------------------
  //{
  //
  //}
  
  //----------------------------------------------------------------
  bool CBAlgoProhibitAllTracks::Bool(const ::cluster::ClusterParamsAlgNew &cluster1,
			       const ::cluster::ClusterParamsAlgNew &cluster2)
  //----------------------------------------------------------------
  {
    //return true means don't prohibit these two clusters
    if(cluster1.GetParams().eigenvalue_principal > _min_EP ||
       cluster2.GetParams().eigenvalue_principal > _min_EP) 
      {
	if(_verbose) 
	  std::cout<<"Prohibiting clusters with EP's of "
		   <<cluster1.GetParams().eigenvalue_principal
		   <<" and "
		   <<cluster2.GetParams().eigenvalue_principal
		   <<std::endl;
	return true;
      }
    return false;
  }

  //------------------------------
  void CBAlgoProhibitAllTracks::Report()
  //------------------------------
  {

  }
    
}
#endif
