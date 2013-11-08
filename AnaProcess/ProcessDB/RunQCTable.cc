#ifndef RUNQCTABLE_CC
#define RUNQCTABLE_CC

#include "RunQCTable.hh"

RunQCTable::RunQCTable() : QCTableBase() 
{ 
  _tablename="RunQCTable"; 
  _table_def  = Form("%s SMALLINT NOT NULL,",QC::kQCFieldName[QC::kMonKey].c_str());
  _table_def += Form("%s INT NOT NULL,",QC::kQCFieldName[QC::kRun].c_str());
  _table_def += Form("%s INT NOT NULL,",QC::kQCFieldName[QC::kSubRun].c_str());
  _table_def += Form("%s DOUBLE PRECISION NOT NULL,",QC::kQCFieldName[QC::kMean].c_str());
  _table_def += Form("%s DOUBLE PRECISION NOT NULL,",QC::kQCFieldName[QC::kSigma].c_str());
  _table_def += Form("%s VARCHAR(100) NOT NULL,",QC::kQCFieldName[QC::kReference].c_str());
  _table_def += Form("%s TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,",QC::kQCFieldName[QC::kLogTime].c_str());
  _table_def += Form("KEY %s, KEY %s, KEY %s, PRIMARY KEY (%s, %s, %s)",
		     QC::kQCFieldName[QC::kMonKey].c_str(),
		     QC::kQCFieldName[QC::kRun].c_str(),
		     QC::kQCFieldName[QC::kSubRun].c_str(),
		     QC::kQCFieldName[QC::kMonKey].c_str(),
		     QC::kQCFieldName[QC::kRun].c_str(),
		     QC::kQCFieldName[QC::kSubRun].c_str());
  Initialize(); 
}

bool RunQCTable::Fetch()
{
  if(_res_key==DB::INVALID_KEY) {
    
    std::cerr << "Fetch(): call this function upon successful Load() call!" << std::endl;
    
    return false;
  }
  
  if(!(GetConnection()->FetchRow(_res_key))) return false;
  
  _run    = GetConnection()->GetRow(_res_key)->GetInt(1);
  _subrun = GetConnection()->GetRow(_res_key)->GetInt(2);
  _mean   = GetConnection()->GetRow(_res_key)->GetDouble(3);
  _sigma  = GetConnection()->GetRow(_res_key)->GetDouble(4);
  _ref    = GetConnection()->GetRow(_res_key)->GetString(5);
  
  return true;
}

void RunQCTable::Initialize() {
  
  QCTableBase::Initialize();
  
}

#endif
