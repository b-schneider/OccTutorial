
//OpenCASCADE Tutorials by Laszlo Kudela
//December 2015

#include "Utilities/inc/MathFunctions.hpp"

#include "Chapter1_Basics/inc/CylinderToBspline.hpp"
#include "Chapter1_Basics/inc/BSplineSurfaceContainer.hpp"
#include "Chapter1_Basics/inc/BSplineBasisComputations.hpp"

#include "math_Matrix.hxx"
#include "BSplCLib.hxx"
#include "TColStd_HArray1OfInteger.hxx"
#include "TColStd_HArray1OfReal.hxx"

#include <iostream>
#include <fstream>


int main(int argc, char *argv[])
{
	//gp_Cylinder cylinder(gp_Ax3(gp::XOY()),50.0);
	//Handle_BSplineSurfaceContainer container = CylinderToBSpline::convertClosedCylinderToBSpline(cylinder,50.0);

	//Standard_Integer flatKnotSequenceLength = BSplCLib::KnotSequenceLength(container->myUMultiplicities->Array1(),2,true);
	//
	//Handle_TColStd_HArray1OfReal flatKnots = new TColStd_HArray1OfReal(1,flatKnotSequenceLength);
	//BSplCLib::KnotSequence(container->myUKnots->Array1(),container->myUMultiplicities->Array1(),2,true,flatKnots->ChangeArray1());	
	//BSplCLib::Reparametrize(0.0,1.0,flatKnots->ChangeArray1());
	//
	//

	Handle_TColStd_HArray1OfReal flatKnots = new TColStd_HArray1OfReal(1,9);
	flatKnots->SetValue(1,-3.0);
	flatKnots->SetValue(2,-2.0);
	flatKnots->SetValue(3,-1.0);
	flatKnots->SetValue(4,0.0);
	flatKnots->SetValue(5,1.0);
	flatKnots->SetValue(6,2.0);
	flatKnots->SetValue(7,3.0);
	flatKnots->SetValue(8,4.0);
	flatKnots->SetValue(9,5.0);


	std::vector<double> samplePoints = MathFunctions::linspace(-1.0,3.0,100);

	std::ofstream file;
	file.open("basisFunctions.txt");
	for(size_t basisFunctionNumber=0;basisFunctionNumber<6;basisFunctionNumber++)
	{
		file << basisFunctionNumber << std::endl;
		for(size_t i=0;i<samplePoints.size();i++)
		{
			Standard_Integer knotIndex;
			Standard_Real newParameter;
			BSplCLib::LocateParameter(2,flatKnots->Array1(),samplePoints[i],true,flatKnots->Value(3),flatKnots->Value(7),knotIndex,newParameter);
			double bSplineValue = BSplineBasisComputations::evaluateBasisFunction(flatKnots,2,newParameter,basisFunctionNumber);
			file << bSplineValue << "\t";
		}
		file << std::endl;
		for(size_t i=0;i<samplePoints.size();i++)
		{
			file << samplePoints[i] << "\t";
		}
		file << std::endl;
	}


}
