// Copyright (C) 2005-2008 Washington University in St Louis, Baylor College of Medicine.  All rights reserved
// Author:        Sasakthi S. Abeysinghe (sasakthi@gmail.com)
// Description:   A clique based fitting tool which attempts to find semi-rigid correspondence between 2 pairs of secondary structure elements

// CVS Meta Information: 
//   $Source$
//   $Revision$
//   $Date$
//   $Author$
//   $State$
//
// History Log: 
//   $Log$
//   Revision 1.9  2009/12/15 04:26:15  ssa1
//   Using GorgonPriorityQueue instead of PriorityQueue
//
//   Revision 1.8  2009/12/07 21:34:36  ssa1
//   Finding Rotation using SVD, and removing compiler warnings
//
//   Revision 1.7  2009/11/30 04:23:44  ssa1
//   Triangle based A* search for flexible fitting
//
//   Revision 1.6  2009/11/19 18:19:25  ssa1
//   Improved flexible fitting.. (Split nodes to guarantee direction)
//
//   Revision 1.5  2009/11/04 20:29:38  ssa1
//   Implementing Triangle based clique search and chain based flexible fitting.
//
//   Revision 1.4  2009/10/13 18:09:34  ssa1
//   Refactoring Volume.h
//
//   Revision 1.3  2009/09/29 19:23:39  ssa1
//   Fixing indexing bugs when performing sse correspondence search.
//
//   Revision 1.2  2009/09/02 19:06:13  ssa1
//   Working towards flexible fitting
//
//   Revision 1.1  2009/08/26 14:58:55  ssa1
//   Adding in Flexible fitting clique search
//


#ifndef PROTEINMORPH_SSE_CORRESPONDENCE_FINDER
#define PROTEINMORPH_SSE_CORRESPONDENCE_FINDER

#include <MathTools/Vector3D.h>
#include <MathTools/MathLib.h>
#include <vector>
#include <Foundation/GorgonPriorityQueue.h>
#include "SSECorrespondenceFeature.h"
#include "SSECorrespondenceNode.h"
#include "SSECorrespondenceSearchNode.h"
#include <Foundation/GraphBase.h>
#include <GraphMatch/PDBReader.h>
#include <GraphMatch/PDBHelix.h>


using namespace wustl_mm::MathTools;
using namespace wustl_mm::Foundation;
using namespace wustl_mm::GraphMatch;
using namespace std;

namespace wustl_mm {
	namespace Protein_Morph {
		class SSECorrespondenceFinder {
		public:
			SSECorrespondenceFinder();
			void InitializeFeatures(vector<SSECorrespondenceFeature> featureList1, vector<SSECorrespondenceFeature> featureList2);
			void InitializeFeaturesFromPDBFiles(string file1, string file2);
			void InitializeConstants(float rigidityThreshold, float featureChangeThreshold, float rigidityAngleCoeff, 
				float rigidityCentroidDistanceCoeff, float rigidityFeatureChangeCoeff, float rigidComponentCoeff, float intraComponentCoeff, 
				float jointAngleThreshold, float dihedralAngleThreshold, float centroidDistanceThreshold, 
				unsigned int maxSolutionCount);		
			vector< vector < vector<SSECorrespondenceNode> > > GetAStarCliqueBasedFeatureCorrespondence(bool printOutput, bool useDirection);
			vector< vector < vector<SSECorrespondenceNode> > > GetAStarTriangleBasedFeatureCorrespondence(bool printOutput, bool useDirection, bool getSmallCliques);			
			vector < vector<SSECorrespondenceNode> > GetValenceBasedFeatureCorrespondence(bool printOutput, bool useDirection);
			vector < vector<SSECorrespondenceNode> > GetValenceBasedFeatureCorrespondence2(bool printOutput, bool useDirection);
			vector < vector<SSECorrespondenceNode> > GetValenceTriangleBasedFeatureCorrespondence(bool printOutput, bool useDirection, bool getSmallCliques);
			vector < vector<SSECorrespondenceNode> > GetValenceBasedFeatureCorrespondenceSet(bool useTriangleClique, bool useDirection, bool getSmallCliques);
			void PrintFeatureListsMathematica();
		private:
			float GetFeatureCompatibilityScore(SSECorrespondenceFeature feature1, SSECorrespondenceFeature feature2);
			float GetFeaturePairRigidityScore(SSECorrespondenceFeature p1, SSECorrespondenceFeature q1, bool isForward1, SSECorrespondenceFeature p2, SSECorrespondenceFeature q2, bool isForward2, bool useDirection);		
			void GetFeatureAngles(float & joint1, float & joint2, float & dihedral, SSECorrespondenceFeature feature1, SSECorrespondenceFeature feature2);
			void GetFeatureAngles(float & joint1, float & joint2, float & dihedral, Vector3DFloat p, Vector3DFloat pDir, Vector3DFloat q, Vector3DFloat qDir);
			vector< vector<float> > GetAllFeatureCompatibilityScores();
			vector<SSECorrespondenceNode> GetAllNodes(vector< vector<float> > & featureCompatibilityScores, bool splitOnDirection);
			vector< vector<float> > GetAllNodePairCompatibilityScores(vector<SSECorrespondenceNode> & nodes, bool useDirection);
			bool IsFeaturePairRigid(SSECorrespondenceNode n1, SSECorrespondenceNode n2, bool useDirection);	
			bool IsFeaturePairRigid(SSECorrespondenceFeature p1, SSECorrespondenceFeature q1, bool isForward1, SSECorrespondenceFeature p2, SSECorrespondenceFeature q2, bool isForward2, bool useDirection);
			void AnalyzeCorrespondence(vector<unsigned int> pFeatures, vector<unsigned int> qFeatures);
			GraphBase<unsigned int, bool> RemoveCliqueAndRelatedNodes(GraphBase<unsigned int, bool> parentGraph, vector<unsigned long long> clique);
		private:
			vector<SSECorrespondenceFeature> featureList1;
			vector<SSECorrespondenceFeature> featureList2;
			float rigidityThreshold, featureChangeThreshold, rigidityAngleCoeff, rigidityCentroidDistanceCoeff, featureChangeCoeff, rigidComponentCoeff, intraComponentCoeff;
			float jointAngleThreshold, dihedralAngleThreshold, centroidDistanceThreshold;
			unsigned int maxSolutionCount;
		};

		SSECorrespondenceFinder::SSECorrespondenceFinder() {
			featureList1.clear();
			featureList2.clear();
			rigidityThreshold = 0.0f;
			featureChangeThreshold = 0.0f;
			rigidityAngleCoeff = 10.0f;
			rigidityCentroidDistanceCoeff = 1.0f;
			featureChangeCoeff = 1.0f;
			rigidComponentCoeff = 1.0f;
			intraComponentCoeff = 1.0f;
			maxSolutionCount = 5;
		}

		void SSECorrespondenceFinder::InitializeFeatures(vector<SSECorrespondenceFeature> featureList1, vector<SSECorrespondenceFeature> featureList2) {
			this->featureList1 = featureList1;
			this->featureList2 = featureList2;
		}

		void SSECorrespondenceFinder::InitializeFeaturesFromPDBFiles(string file1, string file2) {
			vector<PDBHelix> helices1 = PDBReader::ReadHelixPositions(file1);
			vector<PDBHelix> helices2 = PDBReader::ReadHelixPositions(file2);

			for(unsigned int i = 0; i < helices1.size(); i++) {
				featureList1.push_back(SSECorrespondenceFeature(helices1[i].GetEndPosition(0), helices1[i].GetEndPosition(1)));
			}
			for(unsigned int i = 0; i < helices2.size(); i++) {
				featureList2.push_back(SSECorrespondenceFeature(helices2[i].GetEndPosition(0), helices2[i].GetEndPosition(1)));
			}
			helices1.clear();
			helices2.clear();
		}

		void SSECorrespondenceFinder::InitializeConstants(float rigidityThreshold, float featureChangeThreshold, float rigidityAngleCoeff, float rigidityCentroidDistanceCoeff, float rigidityFeatureChangeCoeff, float rigidComponentCoeff, float intraComponentCoeff, float jointAngleThreshold, float dihedralAngleThreshold, float centroidDistanceThreshold, unsigned int maxSolutionCount) {
			this->rigidityThreshold = rigidityThreshold;
			this->featureChangeThreshold = featureChangeThreshold;
			this->rigidityAngleCoeff = rigidityAngleCoeff;
			this->rigidityCentroidDistanceCoeff = rigidityCentroidDistanceCoeff;
			this->featureChangeCoeff = featureChangeCoeff;
			this->rigidComponentCoeff = rigidComponentCoeff;
			this->intraComponentCoeff = intraComponentCoeff;
			this->jointAngleThreshold = jointAngleThreshold;
			this->dihedralAngleThreshold = dihedralAngleThreshold;
			this->centroidDistanceThreshold = centroidDistanceThreshold;
			this->maxSolutionCount = maxSolutionCount;
		}

		float SSECorrespondenceFinder::GetFeatureCompatibilityScore(SSECorrespondenceFeature feature1, SSECorrespondenceFeature feature2) {
			//return pow(feature1.Length() - feature2.Length(), 2);
			return abs(feature1.Length() - feature2.Length());
		}

		float SSECorrespondenceFinder::GetFeaturePairRigidityScore(SSECorrespondenceFeature p1, SSECorrespondenceFeature q1, bool isForward1, SSECorrespondenceFeature p2, SSECorrespondenceFeature q2, bool isForward2, bool useDirection) {
			float pJoint1, pJoint2, pDihedral, qJoint1, qJoint2, qDihedral;
			Vector3DFloat q1p, q1Dir, q2p, q2Dir;

			if(useDirection) {	
				GetFeatureAngles(pJoint1, pJoint2, pDihedral, p1.GetEndPoint(0), p1.GetFeatureVector(), p2.GetEndPoint(0), p2.GetFeatureVector());
				if(isForward1) {
					q1p = q1.GetEndPoint(0);
					q1Dir = q1.GetFeatureVector();
				} else {
					q1p = q1.GetEndPoint(1);
					q1Dir = -q1.GetFeatureVector();
				}

				if(isForward2) {
					q2p = q2.GetEndPoint(0);
					q2Dir = q2.GetFeatureVector();
				} else {
					q2p = q2.GetEndPoint(1);
					q2Dir = -q2.GetFeatureVector();
				}

				GetFeatureAngles(qJoint1, qJoint2, qDihedral, q1p, q1Dir, q2p, q2Dir);
			} else {
				GetFeatureAngles(pJoint1, pJoint2, pDihedral, p1, p2);
				GetFeatureAngles(qJoint1, qJoint2, qDihedral, q1, q2);
			}

			float angleDifference = abs(pJoint1 - qJoint1) + abs(pJoint2 - qJoint2) + abs(pDihedral - qDihedral);
			float centroidDistance = abs((p1.GetCentroid() - p2.GetCentroid()).Length() - (q1.GetCentroid() - q2.GetCentroid()).Length());

			return rigidityAngleCoeff * angleDifference + rigidityCentroidDistanceCoeff * centroidDistance;
		}

		void SSECorrespondenceFinder::GetFeatureAngles(float & joint1, float & joint2, float & dihedral, SSECorrespondenceFeature feature1, SSECorrespondenceFeature feature2) {
			Vector3DFloat f1 = Vector3DFloat::Normalize(feature1.GetFeatureVector());
			Vector3DFloat f2 = Vector3DFloat::Normalize(feature2.GetFeatureVector());
			Vector3DFloat c = Vector3DFloat::Normalize(feature1.GetCentroid() - feature2.GetCentroid());
			joint1 = acos(f1 * c);
			joint1 = min(joint1, (float)(PI-joint1));
			joint2 = acos(f2 * c);
			joint2 = min(joint2, (float)(PI-joint2));

			Vector3DFloat f1n = Vector3DFloat::Normalize(f1 - c * (f1*c));
			Vector3DFloat f2n = Vector3DFloat::Normalize(f2 - c * (f2*c));
			dihedral = acos(f1n * f2n);
			dihedral = min(dihedral, (float)(PI-dihedral));
		}

		void SSECorrespondenceFinder::GetFeatureAngles(float & joint1, float & joint2, float & dihedral, Vector3DFloat p, Vector3DFloat pDir, Vector3DFloat q, Vector3DFloat qDir) {

			Vector3DFloat f1 = Vector3DFloat::Normalize(pDir);
			Vector3DFloat f2 = Vector3DFloat::Normalize(qDir);
			Vector3DFloat c = Vector3DFloat::Normalize((p+p+pDir)*0.5 - (q+q+qDir)*0.5);
			joint1 = acos(f1 * c);
			joint2 = acos(f2 * c);

			Vector3DFloat f1n = Vector3DFloat::Normalize(f1 - c * (f1*c));
			Vector3DFloat f2n = Vector3DFloat::Normalize(f2 - c * (f2*c));
			dihedral = acos(f1n * f2n);
		}

		vector< vector<float> > SSECorrespondenceFinder::GetAllFeatureCompatibilityScores() {
			vector< vector<float> > scores;
			vector<float> scoreRow;
			for(unsigned int i = 0; i < featureList1.size(); i++) {
				scoreRow.clear();
				for(unsigned int j = 0; j < featureList2.size(); j++) {
					scoreRow.push_back(GetFeatureCompatibilityScore(featureList1[i], featureList2[j]));
				}
				scores.push_back(scoreRow);
			}

			//for(unsigned int i = 0; i < featureList1.size(); i++) {
			//	printf("%f %f %f\n", featureList1[i].Length(), featureList2[i].Length(), featureList1[i].Length()- featureList2[i].Length());
			//}
			return scores;
		}

		vector<SSECorrespondenceNode> SSECorrespondenceFinder::GetAllNodes(vector< vector<float> > & featureCompatibilityScores, bool splitOnDirection) {
			vector<SSECorrespondenceNode> nodes;
			for(unsigned int i = 0; i < featureList1.size(); i++) {
				for(unsigned int j = 0; j < featureList2.size(); j++) {
					if(featureCompatibilityScores[i][j] <= featureChangeThreshold) {
						nodes.push_back(SSECorrespondenceNode(i, j, true));
						if(splitOnDirection) {
							nodes.push_back(SSECorrespondenceNode(i, j, false));
						}
					}
				}
			}
			return nodes;
		}

		vector< vector<float> > SSECorrespondenceFinder::GetAllNodePairCompatibilityScores(vector<SSECorrespondenceNode> & nodes, bool useDirection) {
			vector< vector<float> > scores;

			vector<float> scoreRow;
			for(unsigned int i = 0; i < nodes.size(); i++) {
				scoreRow.clear();
				for(unsigned int j = 0; j < nodes.size(); j++) {
					scoreRow.push_back(0.0f);
				}
				scores.push_back(scoreRow);
			}

			unsigned int p1, p2, q1, q2;
			bool isForward1, isForward2;
			for(unsigned int i = 0; i < nodes.size()-1; i++) {
				p1 = nodes[i].GetPIndex();
				q1 = nodes[i].GetQIndex();
				isForward1 = nodes[i].IsForward();
				for(unsigned int j = i+1; j < nodes.size(); j++) {
					p2 = nodes[j].GetPIndex();
					q2 = nodes[j].GetQIndex();
					isForward2 = nodes[i].IsForward();
					scores[i][j] = GetFeaturePairRigidityScore(featureList1[p1], featureList2[q1], isForward1, featureList1[p2], featureList2[q2], isForward2, useDirection);
					scores[j][i] = scores[i][j];
				}
			}

			return scores;			
		}

		bool SSECorrespondenceFinder::IsFeaturePairRigid(SSECorrespondenceNode n1, SSECorrespondenceNode n2, bool useDirection) {
			return IsFeaturePairRigid(featureList1[n1.GetPIndex()], featureList2[n1.GetQIndex()], n1.IsForward(), featureList1[n2.GetPIndex()], featureList2[n2.GetQIndex()], n2.IsForward(), useDirection);			
		}

		bool SSECorrespondenceFinder::IsFeaturePairRigid(SSECorrespondenceFeature p1, SSECorrespondenceFeature q1, bool isForward1, SSECorrespondenceFeature p2, SSECorrespondenceFeature q2, bool isForward2, bool useDirection) {
			float pJoint1, pJoint2, pDihedral, qJoint1, qJoint2, qDihedral;
			bool retVal = true;						

			if(useDirection) {	
				GetFeatureAngles(pJoint1, pJoint2, pDihedral, p1.GetEndPoint(0), p1.GetFeatureVector(), p2.GetEndPoint(0), p2.GetFeatureVector());
				Vector3DFloat q1p, q1Dir, q2p, q2Dir;
				if(isForward1) {
					q1p = q1.GetEndPoint(0);
					q1Dir = q1.GetFeatureVector();
				} else {
					q1p = q1.GetEndPoint(1);
					q1Dir = -q1.GetFeatureVector();
				}

				if(isForward2) {
					q2p = q2.GetEndPoint(0);
					q2Dir = q2.GetFeatureVector();
				} else {
					q2p = q2.GetEndPoint(1);
					q2Dir = -q2.GetFeatureVector();
				}

				GetFeatureAngles(qJoint1, qJoint2, qDihedral, q1p, q1Dir, q2p, q2Dir);
			} else {
				GetFeatureAngles(pJoint1, pJoint2, pDihedral, p1, p2);
				GetFeatureAngles(qJoint1, qJoint2, qDihedral, q1, q2);
			}

			retVal = retVal && (abs(pJoint1 - qJoint1) <= jointAngleThreshold);
			retVal = retVal && (abs(pJoint2 - qJoint2) <= jointAngleThreshold);
			retVal = retVal && (abs(pDihedral - qDihedral) <= dihedralAngleThreshold);

			float centroidDistance = abs((p1.GetCentroid() - p2.GetCentroid()).Length() - (q1.GetCentroid() - q2.GetCentroid()).Length());

			retVal = retVal && (centroidDistance <= centroidDistanceThreshold);

			return retVal;
		}

		vector< vector < vector<SSECorrespondenceNode> > > SSECorrespondenceFinder::GetAStarCliqueBasedFeatureCorrespondence(bool printOutput, bool useDirection) {
			vector< vector < vector<SSECorrespondenceNode> > > correspondence;
			vector< vector<float> > featureCompatibilityScores = GetAllFeatureCompatibilityScores();
			vector<SSECorrespondenceNode> nodes = GetAllNodes(featureCompatibilityScores, useDirection);
			vector< vector<float> > pairCompatibility = GetAllNodePairCompatibilityScores(nodes, useDirection);

			GraphBase<unsigned int, bool> parentGraph;

			for(unsigned int i = 0; i < nodes.size(); i++) {
				parentGraph.AddVertex(featureCompatibilityScores[nodes[i].GetPIndex()][nodes[i].GetQIndex()], i);
			}

			for(int i = 0; i < (int)nodes.size()-1; i++) {
				for(int j = i+1; j < (int)nodes.size(); j++) {
					if((nodes[i].GetPIndex() != nodes[j].GetPIndex()) && 
						(nodes[i].GetQIndex() != nodes[j].GetQIndex()) &&
						(i != j) && (pairCompatibility[i][j] <= rigidityThreshold)) {
						parentGraph.AddEdge(i, j, pairCompatibility[i][j], false);
					}
				}
			}
			vector< vector<unsigned int> > parentSolution;
			vector<unsigned int> parentSolutionElement;
			parentSolution.push_back(parentSolutionElement);

			SSECorrespondenceSearchNode * parentNode = new SSECorrespondenceSearchNode(parentGraph, parentSolution, 0.0f);			

			GorgonPriorityQueue<float, SSECorrespondenceSearchNode *> nodeQueue = GorgonPriorityQueue<float, SSECorrespondenceSearchNode *>(false);
			nodeQueue.Add(parentNode->GetCost(), parentNode);

			unsigned int solutionCount = 0;
			SSECorrespondenceSearchNode * currentNode;
			vector<SSECorrespondenceSearchNode *> childNodes;
			float currentCost;
			while((solutionCount < maxSolutionCount) && !nodeQueue.IsEmpty()) {
				nodeQueue.PopFirst(currentCost, currentNode);
				//currentNode->PrintSolution(nodes);	
				childNodes = currentNode->GetChildNodes(nodes, pairCompatibility, featureChangeCoeff, rigidComponentCoeff, intraComponentCoeff);
				if(childNodes.size() == 0) {
					//printf("Solution found: \t");
					if(printOutput) {
						currentNode->PrintSolution(nodes, useDirection);							
					}
					
					solutionCount++;
				} else {
					//printf("Child Nodes: \n");
					for(unsigned int i = 0; i < childNodes.size(); i++) {
						nodeQueue.Add(childNodes[i]->GetCost(), childNodes[i]);					
						//printf("\t");
						//childNodes[i]->PrintSolution(nodes);
					}
				}
				delete currentNode;
			}


			while(!nodeQueue.IsEmpty()) {
				nodeQueue.PopFirst(currentCost, currentNode);
				delete currentNode;
			}					
			
			return correspondence;
		}

		vector< vector < vector<SSECorrespondenceNode> > > SSECorrespondenceFinder::GetAStarTriangleBasedFeatureCorrespondence(bool printOutput, bool useDirection, bool getSmallCliques) {
			vector< vector < vector<SSECorrespondenceNode> > > correspondence;
			vector< vector<float> > featureCompatibilityScores = GetAllFeatureCompatibilityScores();
			vector<SSECorrespondenceNode> nodes = GetAllNodes(featureCompatibilityScores, useDirection);
			vector< vector<float> > pairCompatibility = GetAllNodePairCompatibilityScores(nodes, useDirection);

			GraphBase<unsigned int, bool> parentGraph;

			for(unsigned int i = 0; i < nodes.size(); i++) {
				parentGraph.AddVertex(featureCompatibilityScores[nodes[i].GetPIndex()][nodes[i].GetQIndex()], i);
			}

			for(int i = 0; i < (int)nodes.size()-1; i++) {
				for(int j = i+1; j < (int)nodes.size(); j++) {
					if((nodes[i].GetPIndex() != nodes[j].GetPIndex()) && 
						(nodes[i].GetQIndex() != nodes[j].GetQIndex()) &&
						IsFeaturePairRigid(nodes[i], nodes[j], useDirection)) {						
						parentGraph.AddEdge(i, j, pairCompatibility[i][j], false);
					}
				}
			}

			vector< vector<unsigned int> > parentSolution;
			vector<unsigned int> parentSolutionElement;
			parentSolution.push_back(parentSolutionElement);

			SSECorrespondenceSearchNode * parentNode = new SSECorrespondenceSearchNode(parentGraph, parentSolution, 0.0f);			

			GorgonPriorityQueue<float, SSECorrespondenceSearchNode *> nodeQueue = GorgonPriorityQueue<float, SSECorrespondenceSearchNode *>(false);
			nodeQueue.Add(parentNode->GetCost(), parentNode);

			unsigned int solutionCount = 0;
			SSECorrespondenceSearchNode * currentNode;
			vector<SSECorrespondenceSearchNode *> childNodes;
			float currentCost;
			//TimeManager tm;
			while((solutionCount < maxSolutionCount) && !nodeQueue.IsEmpty()) {
				//tm.PushCurrentTime();
				nodeQueue.PopFirst(currentCost, currentNode);				
				//currentNode->PrintSolution(nodes, true, true);	
				childNodes = currentNode->GetChildNodesTriangleApprox(nodes, featureList1, featureList2, getSmallCliques);
				if(childNodes.size() == 0) {
					//printf("Solution found: \t");
					if(printOutput) {
						currentNode->PrintSolution(nodes, useDirection);							
					}
				
					solutionCount++;
				} else {
					//printf("Child Nodes: \n");
					for(unsigned int i = 0; i < childNodes.size(); i++) {
						nodeQueue.Add(childNodes[i]->GetCost(), childNodes[i]);						
						//printf("\t");
						//childNodes[i]->PrintSolution(nodes);
					}
				}
				//tm.PopAndDisplayTime("Time spent at node: %f \n");
				delete currentNode;
			}


			while(!nodeQueue.IsEmpty()) {
				nodeQueue.PopFirst(currentCost, currentNode);
				delete currentNode;
			}					
			
			return correspondence;
		}

		vector < vector<SSECorrespondenceNode> > SSECorrespondenceFinder::GetValenceBasedFeatureCorrespondence(bool printOutput, bool useDirection) {
			vector< vector<float> > featureCompatibilityScores = GetAllFeatureCompatibilityScores();
			vector<SSECorrespondenceNode> nodes = GetAllNodes(featureCompatibilityScores, useDirection);
			vector< vector<float> > pairCompatibility = GetAllNodePairCompatibilityScores(nodes, useDirection);

			GraphBase<unsigned int, bool> graph;

			for(unsigned int i = 0; i < nodes.size(); i++) {
				graph.AddVertex(featureCompatibilityScores[nodes[i].GetPIndex()][nodes[i].GetQIndex()], i);
			}

			for(int i = 0; i < (int)nodes.size()-1; i++) {
				for(int j = i+1; j < (int)nodes.size(); j++) {
					if((nodes[i].GetPIndex() != nodes[j].GetPIndex()) && 
						(nodes[i].GetQIndex() != nodes[j].GetQIndex()) &&
						IsFeaturePairRigid(nodes[i], nodes[j], useDirection)) {						
						graph.AddEdge(i, j, pairCompatibility[i][j], false);
					}
				}
			}

			vector< vector<unsigned int> > sol2;
			SSECorrespondenceSearchNode node = SSECorrespondenceSearchNode(graph, sol2, 0.0f);

			unsigned long long vertexIx;
			vector<unsigned long long> neighbors;
			while(graph.GetVertexCount() > 0) {				
				vertexIx = graph.GetHighestValenceVertexIx();
				vector<unsigned long long> clique = graph.VertexSetToVector(graph.GetLowestCostCliqueInOneRing(vertexIx));
				vector<unsigned int> cliqueSol;
				for(unsigned int i = 0; i < clique.size(); i++) {
					cliqueSol.push_back(graph.GetVertex(clique[i]).GetTag());
				}
				vector< vector<unsigned int> > sol = node.GetSolution();
				sol.push_back(cliqueSol);
				node = SSECorrespondenceSearchNode(node.GetChildGraph(nodes, clique), sol, 0);
				graph = node.GetGraph();
			}
			if(printOutput) {
				node.PrintSolution(nodes, useDirection);
			}
			return node.GetSolution(nodes);
		}

		vector < vector<SSECorrespondenceNode> > SSECorrespondenceFinder::GetValenceTriangleBasedFeatureCorrespondence(bool printOutput, bool useDirection, bool getSmallCliques) {
			TimeManager m;
			m.PushCurrentTime();
			m.PushCurrentTime();
			vector< vector<float> > featureCompatibilityScores = GetAllFeatureCompatibilityScores();
			vector<SSECorrespondenceNode> nodes = GetAllNodes(featureCompatibilityScores, useDirection);
			m.PopAndDisplayTime("(*Created Nodes :%f s*)\n");
			m.PushCurrentTime();
			vector< vector<float> > pairCompatibility = GetAllNodePairCompatibilityScores(nodes, useDirection);
			m.PopAndDisplayTime("(*Got edge compatibility:%f s*)\n");

			m.PushCurrentTime();
			GraphBase<unsigned int, bool> graph;

			for(unsigned int i = 0; i < nodes.size(); i++) {
				graph.AddVertex(featureCompatibilityScores[nodes[i].GetPIndex()][nodes[i].GetQIndex()], i);
			}

			for(int i = 0; i < (int)nodes.size()-1; i++) {
				for(int j = i+1; j < (int)nodes.size(); j++) {
					if((nodes[i].GetPIndex() != nodes[j].GetPIndex()) && 
						(nodes[i].GetQIndex() != nodes[j].GetQIndex()) &&
						IsFeaturePairRigid(nodes[i], nodes[j], useDirection)) {						
						graph.AddEdge(i, j, pairCompatibility[i][j], false);
					}
				}
			}
			m.PopAndDisplayTime("(*Create base graph:%f s*)\n");

			vector< vector<unsigned int> > sol2;
			SSECorrespondenceSearchNode node = SSECorrespondenceSearchNode(graph, sol2, 0.0f);

			vector<unsigned long long> neighbors;
			while(graph.GetVertexCount() > 0) {				
				m.PushCurrentTime();
				vector<unsigned long long> clique = graph.VertexSetToVector(graph.GetLowestCostCliqueTriangleApprox(getSmallCliques, getSmallCliques));
				m.PopAndDisplayTime("  (*Got clique%f s*)\n");

				vector<unsigned int> cliqueSol;
				for(unsigned int i = 0; i < clique.size(); i++) {
					cliqueSol.push_back(graph.GetVertex(clique[i]).GetTag());
				}
				vector< vector<unsigned int> > sol = node.GetSolution();
				sol.push_back(cliqueSol);
				node = SSECorrespondenceSearchNode(node.GetChildGraph(nodes, clique), sol, 0);
				graph = node.GetGraph();
			}			
			if(printOutput) {
				node.PrintSolution(nodes, useDirection);
			}
			m.PopAndDisplayTime("(*Done!:%f s*)\n");
			return node.GetSolution(nodes);
		}

		vector < vector<SSECorrespondenceNode> > SSECorrespondenceFinder::GetValenceBasedFeatureCorrespondenceSet(bool useTriangleClique, bool useDirection, bool getSmallCliques) {
			maxSolutionCount = 1;
			vector < vector<SSECorrespondenceNode> > corr, corrItem;
			vector<SSECorrespondenceNode> corrItemItem;
			bool found = true;

			vector<unsigned int> featureList2Indices;
			for(unsigned int i = 0; i < featureList2.size(); i++) {
				featureList2Indices.push_back(i);
			}

			while (found) {
				found = false;
				if(featureList2.size() > 0) {
					if(useTriangleClique) {
						corrItem = GetValenceTriangleBasedFeatureCorrespondence(false, useDirection, getSmallCliques);
					} else {
						corrItem = GetValenceBasedFeatureCorrespondence(false, useDirection);
					} 
					found = (corrItem.size() > 0);
					if(found) {

						for(unsigned int i = 0; i < corrItem.size(); i++) {
							corrItemItem.clear();
							for(unsigned int j = 0; j < corrItem[i].size(); j++) {
								corrItemItem.push_back(SSECorrespondenceNode(corrItem[i][j].GetPIndex(), featureList2Indices[corrItem[i][j].GetQIndex()], corrItem[i][j].IsForward()));
							}
							corr.push_back(corrItemItem);
						}

						bool remove;
						for(int i = (int)featureList2.size()-1;  i >= 0; i--) {
							remove = false;
							for(unsigned int j = 0; !remove && (j < corrItem.size()); j++) {
								for(unsigned int k = 0; !remove && (k < corrItem[j].size()); k++) {
									remove = remove || (corrItem[j][k].GetQIndex() == i);
								}
							}
							if(remove) {
								featureList2.erase(featureList2.begin() + i);
								featureList2Indices.erase(featureList2Indices.begin() + i);	
							}
						}
					}
				}
			}


			printf("corr = {\n");
			for(unsigned int i = 0; i < corr.size(); i++) {
				if(i != 0) {
					printf(",\n");
				}
				printf("\t{");
				for(unsigned int j = 0; j < corr[i].size(); j++) {
					if(j != 0) {
						printf(", ");
					}
					if(useDirection) {
						if(corr[i][j].IsForward()) {
							printf("{{%d, %d}, {%d, %d}}", corr[i][j].GetPIndex(), 0, corr[i][j].GetQIndex(), 0);
						} else {
							printf("{{%d, %d}, {%d, %d}}", corr[i][j].GetPIndex(), 0, corr[i][j].GetQIndex(), 1);
						}
					} else {
						printf("{%d, %d}", corr[i][j].GetPIndex(), corr[i][j].GetQIndex());
					}
				}
				printf("}");
			}
			printf("};\n");
			printf("corr = Sort[corr, Length[#1] > Length[#2] &];\n");
			printf("printFinalOutput[corr, fl1, fl2, 1]\n");

			return corr;
		}

		void SSECorrespondenceFinder::PrintFeatureListsMathematica() {
			Vector3DFloat pt0, pt1;
			printf("fl1 = {\n");
			for(unsigned int i = 0; i < featureList1.size(); i++) {
				pt0 = featureList1[i].GetEndPoint(0);
				pt1 = featureList1[i].GetEndPoint(1);
				if(i != 0) {
					printf(",\n");
				}
				printf("\t{{%f, %f, %f}, {%f, %f, %f}}", pt0.X(), pt0.Y(), pt0.Z(), pt1.X(), pt1.Y(), pt1.Z());
			}
			printf("};\n\n");

			printf("fl2 = {\n");
			for(unsigned int i = 0; i < featureList2.size(); i++) {
				pt0 = featureList2[i].GetEndPoint(0);
				pt1 = featureList2[i].GetEndPoint(1);
				if(i != 0) {
					printf(",\n");
				}
				printf("\t{{%f, %f, %f}, {%f, %f, %f}}", pt0.X(), pt0.Y(), pt0.Z(), pt1.X(), pt1.Y(), pt1.Z());
			}
			printf("};\n\n");
		}
	}
}


#endif