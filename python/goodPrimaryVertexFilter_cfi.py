## $Id: goodPrimaryVertexFilter_cfi.py,v 1.1 2012/05/24 11:33:04 mschrode Exp $
##
## Standard requirement for a good primary vertex as recommended in
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCollisionsDataAnalysis#Analysis_of_the_processed_data

import FWCore.ParameterSet.Config as cms
goodPrimaryVertexFilter = cms.EDFilter(
    "GoodVertexFilter",
    vertexCollection = cms.InputTag('offlinePrimaryVertices'),
    minimumNDOF = cms.uint32(4) ,
    maxAbsZ = cms.double(24),
    maxd0 = cms.double(2) 
    )
