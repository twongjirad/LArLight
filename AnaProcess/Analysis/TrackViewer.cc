#ifndef TRACKVIEWER_CC
#define TRACKVIEWER_CC

#include "TrackViewer.hh"

//################################################################
TrackViewer::TrackViewer() : ana_base(), _hRecoTrack_v()
//################################################################
{
  // Class name
  _name = "TrackViewer";
  // Set initialization values for pointers
  _fout     = 0;
  _c1       = 0;
  _p1       = 0;
  _hRecoSPS = 0;
  _hMCStep  = 0;
}

//################################################################
bool TrackViewer::initialize()
//################################################################
{
  // Make canvas & pad
  if(_c1) {delete _c1; _c1=0;};
  if(_p1) {delete _p1; _p1=0;};

  _c1 = new TCanvas("_cTrackViewer","",600,500);
  _p1 = new TPad("_pTrackViewer","",0.01, 0.01, 0.99, 0.99);

  _c1->Draw();
  _p1->Draw();

  return true;
}

//################################################################
bool TrackViewer::analyze(storage_manager* storage)
//################################################################
{
  
  // Clean up histograms if they already exist (from previous event)
  if(_hMCStep)  {delete _hMCStep;  _hMCStep  = 0;};
  if(_hRecoSPS) {delete _hRecoSPS; _hRecoSPS = 0;};
  for(auto h : _hRecoTrack_v) {delete h; h=0;};
  _hRecoTrack_v.clear();

  //
  // Obtain event-wise data object pointers
  //
  event_sps*   ev_sps    = (event_sps*)   ( storage->get_data(DATA::SpacePoint)  );
  event_track* ev_kalsps = (event_track*) ( storage->get_data(DATA::Kalman3DSPS) );
  event_mc*    ev_mc     = (event_mc*)    ( storage->get_data(DATA::MCTruth)     );

  // Define utility variables to hold max/min of each axis range
  double xmax, ymax, zmax;
  xmax = ymax = zmax = -1.;
  double xmin, ymin, zmin;
  xmin = ymin = zmin = 999999.;

  // Find max/min boundary for all axis (spacepoint and track)
  if(ev_sps)

    ev_sps->get_axis_range(xmax, xmin, ymax, ymin, zmax, zmin);

  if(ev_kalsps)

    ev_kalsps->get_axis_range(xmax, xmin, ymax, ymin, zmax, zmin);

  //if(ev_mc)

  //ev_mc->get_axis_range(xmax, xmin, ymax, ymin, zmax, zmin);

  // Proceed only if minimum/maximum are set to some values other than the defaults
  if(xmax == -1) {

    print(MSG::WARNING,__FUNCTION__,
	  "Did not find any reconstructed spacepoint or track. Skipping this event...");

    return true;
  }

  //
  // Make & fill vertex histograms
  //

  // Spacepoints
  if(ev_sps) {
    
    const std::vector<spacepoint> sps_v = ev_sps->GetSPSCollection();

    _hRecoSPS = Prepare3DHisto("_hRecoSPS", xmin, xmax, ymin, ymax, zmin, zmax);

    for(auto sps : sps_v)

      _hRecoSPS->Fill(sps.XYZ()[0], sps.XYZ()[1], sps.XYZ()[2]);
    
    _hRecoSPS->SetMarkerStyle(23);
    _hRecoSPS->SetMarkerColor(kBlue);
  }

  // Tracks
  if(ev_kalsps) {

    const std::vector<track> track_v = ev_kalsps->GetTrackCollection();

    for(auto const& trk : track_v){
      
      TH3D* h=0;
      h=Prepare3DHisto(Form("_hKalman3DSPS_%03d",(int)(_hRecoTrack_v.size())),
		       xmin,xmax,ymin,ymax,zmin,zmax);

      for(size_t i=0; i<trk.n_point(); i++) {

	const TVector3 vtx = trk.vertex_at(i);

	h->Fill(vtx[0],vtx[1],vtx[2]);

      }

      h->SetMarkerStyle(22);
      h->SetMarkerColor(kRed);
      _hRecoTrack_v.push_back(h);

    }
    
  }

  // MC trajectory points
  if(ev_mc){

    const std::vector<part_mc> part_v = ev_mc->GetParticleCollection();

    for(auto const& part : part_v){

      // Only care about a primary particle
      if(part.track_id() != 1)

	continue;

      const std::vector<TVector3> vertex_v = part.step_vertex();

      _hMCStep = Prepare3DHisto("_hMCStep",
				xmin,xmax,ymin,ymax,zmin,zmax);
      
      for(auto const& vtx : vertex_v) 
	
	_hMCStep->Fill(vtx[0],vtx[1],vtx[2]);

      _hMCStep->SetMarkerStyle(20);
      _hMCStep->SetMarkerColor(kCyan);
      break; // Only make 1 histogram
    }
  }

  // Draw histograms
  DrawCanvas();

  return true;
};

//################################################################
void TrackViewer::DrawCanvas()
//################################################################
{

  _p1->cd();
  bool first_draw = true;

  // 
  // Drawing order is from the histogram with many points => less points
  // otherwise it would be hard to see histograms with less points!
  // This means we draw MC, SpacePoint, then Track
  //

  if(_hMCStep){

    print(MSG::NORMAL,__FUNCTION__,Form("Drawing %d MC trajectory points...",(int)(_hMCStep->GetEntries())));
    
    if(first_draw) {

      _hMCStep->Draw(); 

      first_draw=false;

    }

    else _hMCStep->Draw("sames");

  }

  if(_hRecoSPS) {

    print(MSG::NORMAL,__FUNCTION__,"Drawing space points...");

    if(first_draw) {

      _hRecoSPS->Draw();

      first_draw=false;

    }

    else _hRecoSPS->Draw("sames");

  }

  if(_hRecoTrack_v.size())

    print(MSG::NORMAL,__FUNCTION__,Form("Drawing %zu reco tracks...",_hRecoTrack_v.size()));

  for(auto h : _hRecoTrack_v) {
    
    if(first_draw) {
      h->Draw(); 
      first_draw=false;
    }
    else h->Draw("sames");
  }

  // Update canvas if anything is drawn otherwise clear
  if(first_draw) _p1->Clear();
  else{
    _c1->Modified();
    _c1->Update();
    _p1->Modified();
    _p1->Update();
    _p1->Draw();
  }

}

//################################################################
TH3D* TrackViewer::Prepare3DHisto(std::string name, 
				  double xmin, double xmax,
				  double ymin, double ymax,
				  double zmin, double zmax)
//################################################################
{

  TH3D* h=0;
  if(h) delete h;

  h = new TH3D(name.c_str(),"3D Viewer; X; Y; Z",
	       50,  xmin, xmax,
	       50,  ymin, ymax,
	       300, zmin, zmax);

  return h;
}

bool TrackViewer::finalize() {

  // This function is called at the end of event loop.
  // Do all variable finalization you wish to do here.
  // If you need, you can store your ROOT class instance in the output
  // file. You have an access to the output file through "_fout" pointer.

  return true;
}

#endif
