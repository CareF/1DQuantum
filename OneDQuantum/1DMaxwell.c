/**
 *
 * \file
 *
 * \brief Compute 1D Coulomb field using Maxwell's equations
 *
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#ifdef __MP /*openmp support*/
#include <omp.h>
#endif 
#include "science.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef _WINDLL
__declspec(dllexport)
#endif 

/**
 * 
 * \brief Compute Coulomb field
 *  
 * Calculate Coulomb Field generated by charge density eDensity(x) and 
 * dielectric constant eps(x), assuming at x=0 the field is 0 V/cm, 
 * the voltage is 0
 * in the range x0 <= x < x0 + step*N
 * eDensity is in unit # of elementary charge / Angstrom^-3 (electrons:-)
 * eps is relative dielectric constant, in unit epsilon_0
 * step is in unit Angstrom
 * Return the displacement at the x0 + step*N, and put the field (in V) 
 * in *Vc
 */
double CoulombField(double step, numpyint N, 
		const double *eDensity, const double *eps,
		double *Vc) {
       	int i;
	const double eUnit = e0*step;
	/* Electrical displacement is half a step ahead of Vc */
	double D = eDensity[0]*eUnit/2; 
	Vc[0] = 0;
	for(i=1; i<N; i++) {
		Vc[i] = Vc[i-1] - D / (eps0*eps[i]) * step;
		D += (eDensity[i]+eDensity[i-1])/2*eUnit;
	}
	D += eDensity[N-1]*eUnit/2;
	return D;
}


#ifdef _WINDLL
__declspec(dllexport)
#endif 
/**
 * \brief Coulomb field with anti-periodic boundary condition
 * 
 * Same with CoulombField but return VC so that D[0] = -D[N]
 * with is a nature conditon for charge in vaccum. 
 */
double CoulombField0(double step, numpyint N, 
		const double *eDensity, const double *eps,
		double *Vc) {
       	int i;
	double D = CoulombField(step, N, eDensity, eps, Vc);
	D = D/2;
	for(i=0; i<N; i++) {
		Vc[i] += D/(eps0 * eps[i])*i*step;
	}
	return D;
}


#ifdef _WINDLL
__declspec(dllexport)
#endif 
numpyint speedOfLight()
{return 299792458;}


#ifdef __cplusplus
}
#endif

