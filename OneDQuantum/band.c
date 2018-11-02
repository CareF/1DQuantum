#include "band.h"
/* add Wurtzite structure */
/* Zincblende structure band, compatiable with structure BAND */
numpyint UpdateBand(Band *band, double E, const double *xVc, double *m) {
	return band->update(band, E, xVc, m);
}
typedef struct ZBBAND {
	UpdateFunc updateM;
	numpyint N;
	const double *xEg;
	const double *xF;
	const double *xEp; 
	const double *xESO;
}ZBBand; 

/* Update effective mass of a Zincblende band semiconductor */
numpyint ZBupdateM(Band *mat, double Eq, const double *xVc, double *m) {
	ZBBand *zbmat = (ZBBand *) mat;
	int q; 
	for(q=0; q<zbmat->N; q++) {
		m[q] = 1 / (1 + 2*zbmat->xF[q] + zbmat->xEp[q]/3 * ( 
					2 / (Eq - xVc[q] + zbmat->xEg[q]) + 
					1 / (Eq - xVc[q] + zbmat->xEg[q] + zbmat->xESO[q])) );
	}
	return zbmat->N;
}

Band *ZBband_new(numpyint N, const double *xEg, const double *xF,
		const double *xEp, const double *xESO) {
	ZBBand *zbband = (ZBBand *) malloc( sizeof(ZBBand) );
	zbband->updateM = ZBupdateM;
	zbband->N = N; 
	zbband->xEg = xEg; 
	zbband->xF = xF; 
	zbband->xEp = xEp; 
	zbband->xESO = xESO;
	return (Band *) zbband; 
}

void ZBband_free(Band *zbband) {
	free( (ZBBand *) zbband );
	return;
}

#ifdef __DEBUG
#include <stdio.h>
void ZBband_check(const Band *band, numpyint N, const double *xEg, 
		const double *xF, const double *xEp, const double *xESO) {
	printf("Checking ZBband\n");
	const ZBBand *zbband = (const ZBBand *) band;
	if(zbband->updateM != ZBupdateM)
		printf("ZBupdateM checkfail\n");
	if(zbband->N != N)
		printf("N checkfail\n");
	if(zbband->xEg != xEg) 
		printf("xEg checkfail\n");
	if(zbband->xF != xF)
		printf("xF checkfail\n");
	if(zbband->xEp != xEp)
		printf("xEp checkfail\n");
	if(zbband->xESO != xESO)
		printf("xESO checkfail\n");
	printf("Checking Finished\n");
	return;
}
#endif

