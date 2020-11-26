#include <iostream>
#include <fstream>



void writeMesh(int nPointsI, int nPointsJ){

	//nPoints - počet bodů sítě, ne buněk, nPointsI = nCellsI + 1

	std::ofstream file;

	//počet polí s hodnotama
	const int nFields = 2; 
	int nCells = (nPointsI - 1 ) * (nPointsJ - 1);

	//output file
	file.open("msh.vtk");
	
	//hlavička souboru
	file << "# vtk DataFile Version 3.0" << std::endl << "vtk output" << std::endl << "ASCII" << std::endl << "DATASET STRUCTURED_GRID" << std::endl
	<< "DIMENSIONS "<< nPointsI << " " << nPointsJ << " 1" << std::endl << "POINTS " << nPointsI*nPointsJ << " float" << std::endl;


	//vypsání bodů sítě do souboru
	int i,j;
	for(i=0;i<nPointsI;i++){
		for(j=0;j<nPointsJ;j++){
			file << i << " " << j << " 0" << std::endl; 
		}
	}
	


	file << "CELL_DATA " << nCells << std::endl << "FIELD FieldData " << nFields << std::endl;
	

	//jednotlivé pole s hodnotama

	//skalární pole
	file << "rho 1 " << nCells << " float" << std::endl;
	for(i=0;i<nPointsI-1;i++) {
		for(j=0;j<nPointsJ-1;j++){
		
		// na každém řádku hodnota buňky

 			
		}
	}

	//vektorové pole
	file << "U 3 " << nCells  << " float" << std::endl;
	for(i=1;i<nPointsI;i++) {
		for(j=1;j<nPointsJ;j++){

		//hodnota vektoru rychlosti ve formát ux uy 0 na každém řádku

		//1 2 0
		//0.12 0.3 0
		//...
 
		}
	}

	file.close();
}
