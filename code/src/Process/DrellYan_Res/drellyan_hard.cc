
#include "drellyan_hard.h"


#include "constants.h"
#include "phase_space.h"
#include "drellyan_input.h"
#include "diphoton_hard.h" //for Asmitad etc



void sigmaijdrellyancalc(drellyan_input* drellyan_in, PSpoint& PS, std::vector<std::vector<double> >& sigmaij, double alphas, double& q2) {
// Born partonic cross-sections
// Normalisation is such that the COMPLETE dsigma/dOmega double differential cross-sections are returned

    int Nf = drellyan_in->res_1.Nf;
    double s = 2.*PS.ss(0,1);
    double t = -2.*PS.ss(0,2);
    double costheta = 1. + 2.*t/s;
    double gevpb = drellyan_in->res_1.gevm2topb;
    double Qu = 2./3.;
    double Qd = -1./3.;
    double pi = k_constants::pi;
// EW scheme uses mw, mz and GF as inputs
    double mz = drellyan_in->mz;
    double mw = drellyan_in->mw;
    double ww = drellyan_in->ww;
    double zw = drellyan_in->zw;
    double gw = drellyan_in->gw;
    double gz = drellyan_in->gz; // "gz" is actually e/(2 sW cW) -- note the factor of 2
    double sw2 = drellyan_in->sw2;
    double alphaem = drellyan_in->res_1.alpha_QED;
    double Vud = drellyan_in->Vud;
    double Vus = drellyan_in->Vus;
    double Vub = drellyan_in->Vub;
    double Vcd = drellyan_in->Vcd;
    double Vcs = drellyan_in->Vcs;
    double Vcb = drellyan_in->Vcb;

    double chi1=(q2-mz*mz)/q2;
    double chi2=((q2-mz*mz)*(q2-mz*mz)+mz*mz*zw*zw)/(q2*q2);
    double cLzu=gz*(0.5-Qu*sw2);
    double cLzd=gz*(-0.5-Qd*sw2);
    double cRzu=-gz*Qu*sw2;
    double cRzd=-gz*Qd*sw2;
    double cLz=gz*(-0.5+sw2);
    double cRz=gz*sw2;
    double cLw=gw/(std::pow(2.0,0.5));
// Overall factors for amplitudes
    double flux = 1./2./q2;
    double spincolavg = 1/12.;
    double PSfac = 1/32./pi/pi;
    double totfac = flux*spincolavg*PSfac*gevpb;
    double facZ = totfac * 16.*q2*q2/( (q2-mz*mz)*(q2-mz*mz)+mz*mz*zw*zw );
    double facW = totfac * 16.*q2*q2/( (q2-mw*mw)*(q2-mw*mw)+mw*mw*ww*ww );
//    double facZ = 1/(12.0*pi)*q2/ ((q2-mz*mz)*(q2-mz*mz)+mz*mz*zw*zw) *gevpb/(4*pi);
//    double facW = 1/(12.0*pi)*q2/ ((q2-mw*mw)*(q2-mw*mw)+mw*mw*ww*ww) *gevpb/(4*pi);

    int DYproc = drellyan_in->DYprocess; //Selection of mediator boson if DY, 1 = W+, 2 = W-, 3 = W+ and W-, 4 = Z only, 5 = Z+gamma, set in input file
    int DYnwapprox= drellyan_in->DYnarrowwidthapprox; //Use narrow width approx so on W and Z resonance or not, set in input file


////////////////////////


// W
    if(DYproc == 1 || DYproc == 2 || DYproc == 3) {
      if(DYproc == 1 || DYproc ==3){
// W+ boson
        sigmaij[Nf+1][Nf-2] = facW/16.0*Vud*Vud*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //u dbar
        sigmaij[Nf-2][Nf+1] = facW/16.0*Vud*Vud*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //dbar u
        if(Nf>=3) sigmaij[Nf+1][Nf-3] = facW/16.0*Vus*Vus*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //u sbar
        if(Nf>=3) sigmaij[Nf-3][Nf+1] = facW/16.0*Vus*Vus*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //sbar u
        if(Nf>=5) sigmaij[Nf+1][Nf-5] = facW/16.0*Vub*Vub*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //u bbar
        if(Nf>=5) sigmaij[Nf+1][Nf-5] = facW/16.0*Vub*Vub*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //bbar u
        if(Nf>=4) sigmaij[Nf+4][Nf-3] = facW/16.0*Vcs*Vcs*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //c sbar
        if(Nf>=4) sigmaij[Nf-3][Nf+4] = facW/16.0*Vcs*Vcs*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //sbar c
        if(Nf>=4) sigmaij[Nf+4][Nf-2] = facW/16.0*Vcd*Vcd*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //c dbar
        if(Nf>=4) sigmaij[Nf+4][Nf-2] = facW/16.0*Vcd*Vcd*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //dbar c
        if(Nf>=5) sigmaij[Nf+4][Nf-5] = facW/16.0*Vcb*Vcb*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //c bbar
        if(Nf>=5) sigmaij[Nf-5][Nf+4] = facW/16.0*Vcb*Vcb*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //bbar c
      }
      if(DYproc == 2 || DYproc == 3) { // W- boson
        sigmaij[Nf+2][Nf-1] = facW/16.0*Vud*Vud*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //d ubar
        sigmaij[Nf-1][Nf+2] = facW/16.0*Vud*Vud*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //ubar d
        if(Nf>=3) sigmaij[Nf+3][Nf-1] = facW/16.0*Vus*Vus*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //s ubar
        if(Nf>=3) sigmaij[Nf-1][Nf+3] = facW/16.0*Vus*Vus*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //ubar s
        if(Nf>=5) sigmaij[Nf+5][Nf-1] = facW/16.0*Vub*Vub*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //b ubar
        if(Nf>=5) sigmaij[Nf-1][Nf+5] = facW/16.0*Vub*Vub*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //ubar b
        if(Nf>=4) sigmaij[Nf+3][Nf-4] = facW/16.0*Vcs*Vcs*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //s cbar
        if(Nf>=4) sigmaij[Nf-4][Nf+3] = facW/16.0*Vcs*Vcs*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //cbar s
        if(Nf>=4) sigmaij[Nf+2][Nf-4] = facW/16.0*Vcd*Vcd*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //d cbar
        if(Nf>=4) sigmaij[Nf-4][Nf+2] = facW/16.0*Vcd*Vcd*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //cbar d
        if(Nf>=5) sigmaij[Nf+5][Nf-4] = facW/16.0*Vcb*Vcb*cLw*cLw*cLw*cLw*(1.0+costheta)*(1.0+costheta); //b cbar
        if(Nf>=5) sigmaij[Nf-4][Nf+5] = facW/16.0*Vcb*Vcb*cLw*cLw*cLw*cLw*(1.0-costheta)*(1.0-costheta); //cbar b
      }
    }
    else if (DYproc == 4) { // Z boson only
      sigmaij[Nf+1][Nf-1] = facZ*((cLzu*cLzu+cRzu*cRzu)*(cLz*cLz+cRz*cRz)*(1.0+costheta*costheta) -   (cLzu*cLzu-cRzu*cRzu)*(cLz*cLz-cRz*cRz)*(2.0*costheta)); //u ubar
      if(Nf>=4) sigmaij[Nf+4][Nf-4] = sigmaij[Nf+1][Nf-1]; //c cbar, as u ubar = c cbar
      sigmaij[Nf-1][Nf+1] = facZ*((cLzu*cLzu+cRzu*cRzu)*(cLz*cLz+cRz*cRz)*(1.0+costheta*costheta) +   (cLzu*cLzu-cRzu*cRzu)*(cLz*cLz-cRz*cRz)*(2.0*costheta)); //ubar u
      if(Nf>=4) sigmaij[Nf-4][Nf+4] = sigmaij[Nf-1][Nf+1]; //cbar c, as cbar c = ubar u
      sigmaij[Nf+2][Nf-2] = facZ*((cLzd*cLzd+cRzd*cRzd)*(cLz*cLz+cRz*cRz)*(1.0+costheta*costheta) - (cLzd*cLzd-cRzd*cRzd)*(cLz*cLz-cRz*cRz)*(2.0*costheta)); //d dbar
      if(Nf>=3) sigmaij[Nf+3][Nf-3] = sigmaij[Nf+2][Nf-2]; //s sbar = d dbar
      if(Nf>=5) sigmaij[Nf+5][Nf-5] = sigmaij[Nf+2][Nf-2]; // b bar = d dbar
      sigmaij[Nf-2][Nf+2] = facZ*((cLzd*cLzd+cRzd*cRzd)*(cLz*cLz+cRz*cRz)*(1.0+costheta*costheta) + (cLzd*cLzd-cRzd*cRzd)*(cLz*cLz-cRz*cRz)*(2.0*costheta)); //dbar d
      if(Nf>=3) sigmaij[Nf-3][Nf+3] = sigmaij[Nf-2][Nf+2]; //sbar s = dbar d
      if(Nf>=5) sigmaij[Nf-5][Nf+5] = sigmaij[Nf-2][Nf+2]; //bbar b = dbar d
    }
    else if (DYproc == 5) {// Z boson and gamma* in one, note corrected typos in hep-ph/9704239!
      sigmaij[Nf+1][Nf-1] = facZ*(((cLzu*cLzu + cRzu*cRzu)*(cLz*cLz+cRz*cRz) + 0.25*(4.0*pi*alphaem)*(4.0*pi*alphaem)*Qu*Qu*chi2 -0.5*(4.0*pi*alphaem)*Qu*(cLzu+cRzu)*(cLz+cRz)*chi1)*(1.0+costheta*costheta) - ((cLzu*cLzu-cRzu*cRzu)*(cLz*cLz-cRz*cRz)-0.5*(4.0*pi*alphaem)*Qu*(cLzu-cRzu)*(cLz-cRz)*chi1)*(2.0*costheta)); //u ubar
      if(Nf>=4) sigmaij[Nf+4][Nf-4] = sigmaij[Nf+1][Nf-1]; //c cbar, as u ubar = c cbar
      sigmaij[Nf-1][Nf+1] = facZ*(((cLzu*cLzu + cRzu*cRzu)*(cLz*cLz+cRz*cRz) + 0.25*(4.0*pi*alphaem)*(4.0*pi*alphaem)*Qu*Qu*chi2 -0.5*(4.0*pi*alphaem)*Qu*(cLzu+cRzu)*(cLz+cRz)*chi1)*(1.0+costheta*costheta) + ((cLzu*cLzu-cRzu*cRzu)*(cLz*cLz-cRz*cRz)-0.5*(4.0*pi*alphaem)*Qu*(cLzu-cRzu)*(cLz-cRz)*chi1)*(2.0*costheta)); //ubar u

      if(Nf>=4) sigmaij[Nf-4][Nf+4] = sigmaij[Nf-1][Nf+1]; //cbar c, as cbar c = ubar u

      sigmaij[Nf+2][Nf-2] = facZ*(((cLzd*cLzd+cRzd*cRzd)*(cLz*cLz+cRz*cRz)+0.25*(4.0*pi*alphaem)*(4.0*pi*alphaem)*Qd*Qd*chi2 -0.5*(4.0*pi*alphaem)*Qd*(cLzd+cRzd)*(cLz+cRz)*chi1)*(1.0+costheta*costheta) - ((cLzd*cLzd-cRzd*cRzd)*(cLz*cLz-cRz*cRz)-0.5*(4.0*pi*alphaem)*Qd*(cLzd-cRzd)*(cLz-cRz)*chi1)*(2.0*costheta)); //d dbar
      if(Nf>=3) sigmaij[Nf+3][Nf-3] = sigmaij[Nf+2][Nf-2]; //s sbar = d dbar
      if(Nf>=5) sigmaij[Nf+5][Nf-5] = sigmaij[Nf+2][Nf-2]; // b bar = d dbar

      sigmaij[Nf-2][Nf+2] = facZ*(((cLzd*cLzd+cRzd*cRzd)*(cLz*cLz+cRz*cRz)+0.25*(4.0*pi*alphaem)*(4.0*pi*alphaem)*Qd*Qd*chi2 -0.5*(4.0*pi*alphaem)*Qd*(cLzd+cRzd)*(cLz+cRz)*chi1)*(1.0+costheta*costheta)+ ((cLzd*cLzd-cRzd*cRzd)*(cLz*cLz-cRz*cRz)-0.5*(4.0*pi*alphaem)*Qd*(cLzd-cRzd)*(cLz-cRz)*chi1)*(2.0*costheta)); //dbar d

      if(Nf>=3) sigmaij[Nf-3][Nf+3] = sigmaij[Nf-2][Nf+2]; //sbar s = dbar d
      if(Nf>=5) sigmaij[Nf-5][Nf+5] = sigmaij[Nf-2][Nf+2]; //bbar b = dbar d
    }
    else{
      std::cout << "Wrong DYprocess flag -- STOPPING" << std::endl;
      exit(EXIT_FAILURE);
    }


}
