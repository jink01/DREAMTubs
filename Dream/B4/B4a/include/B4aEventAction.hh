//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4aEventAction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4aEventAction.hh
/// \brief Definition of the B4aEventAction class

#ifndef B4aEventAction_h
#define B4aEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>


/// Event action class 

class B4aEventAction : public G4UserEventAction
{
  public:
    B4aEventAction();
    virtual ~B4aEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void Addem(G4double de);  //Add em component
    void Addem2(G4double de); //Add em component (different estimation)
    void AddScin(G4double de);//Add energy in scintillating fibers
    void AddCher(G4double de);//Add energy in Cherenkov fibers
    void AddCherenkov(G4int n);//Add cherenkov photoelectron
    //void AddScintillation();
    void Addenergy(G4double de);//Add all energy deposited
    //void AddEnergyfibre(G4double de, G4int number);//Add energy in copy number fiber
    //void AddSignalfibre(G4int number);
    void SavePrimaryParticle(G4String name);
    void SaveAbsorberMaterial(G4String AbsorberMaterialName);
    void SavePrimaryEnergy(G4double primaryparticleenergy);
    void AddEscapedEnergy(G4double escapedenergy);

    //to save vectors in ntuple
    std::vector<G4double>& GetVectorSignals() {return VectorSignals;}
    std::vector<G4double>& GetVectorSignalsCher() {return VectorSignalsCher;}
    std::vector<G4double>& GetVectorDepositedEnergy() {return VectorDepositedEnergy;}
    std::vector<G4double>& GetVectorDepositedEScin() {return VectorDepositedEScin;}
    std::vector<G4double>& GetVectorDepositedECher() {return VectorDepositedECher;}
    //std::vector<G4double>& GetVectorSignals() {return VectorSignals[];}
    //std::vector<G4double>& GetVectorSignalsCher() {return VectorSignalsCher[];}

    //to fill vectors
    //void AddVectorScinEnergy(G4double de, G4int fiber); //fill vector of scintillating fibers with energy deposition
    //void AddVectorCherPE(G4int fiber, G4int n);//fill vector of cherenkov fibers with chernekov photoelectrons
    void AddVectorScinEnergy(G4double de, G4int tower, G4int fiber);
    void AddVectorCherPE(G4int tower, G4int fiber, G4int n);
    void AddVectorDepositedEnergy(G4double e, G4int tower);
    void AddVectorDepositedEScin(G4double e, G4int tower);
    void AddVectorDepositedECher(G4double e, G4int tower);
    
  private:
    G4double Energyem; //Energy of em component
    G4double Energyem2; //Energy of em component (different estimation)
    G4double EnergyScin; //Energy in scintillating fibers
    G4double EnergyCher; //Energy in Cherenkov fibers
    G4int     NofCherenkovDetected; //Number of Cherenkov photons detected (in cherenkov fibers)
    //G4int     NofScintillationDetected;//Number of Scintillating photons detected (in scintillating fibers)
    G4double  EnergyTot;//Total energy deposited (does not count invisibile energy)
    //G4double  Signalfibre[64];//Signal in 64 single module fibers, to be used with AddEnergyfibre
    G4String PrimaryParticleName; //Name of primary particle
    G4String AbsorberMaterial; //Name of absorber material
    G4double PrimaryParticleEnergy;//Primary particle energy
    G4double EscapedEnergy;

    std::vector<G4double> VectorSignals;//Vector filled with scintillating fibers energy deposits
    std::vector<G4double> VectorSignalsCher;//Vector filled with Cherenkov fibers Cherenkov photoelectrons

    std::vector<G4double> VectorDepositedEnergy; //Vector of total energy deposited tower by tower
    std::vector<G4double> VectorDepositedEScin; //Vector of deposited energy in S fibers - tower by tower
    std::vector<G4double> VectorDepositedECher; //Vector of deposited energy in C fibers - tower by tower

    //std::vector<std::vector<G4double>> VectorSignals;
    //std::vector<std::vector<G4double>> VectorSignalsCher;
};

// inline functions

inline void B4aEventAction::AddEscapedEnergy(G4double escapedenergy){
  EscapedEnergy += escapedenergy;
}

inline void B4aEventAction::SavePrimaryParticle(G4String name){
  PrimaryParticleName = name;
}

inline void B4aEventAction::SaveAbsorberMaterial(G4String AbsorberMaterialName){
  AbsorberMaterial = AbsorberMaterialName;
}

inline void B4aEventAction::SavePrimaryEnergy(G4double primaryparticleenergy){
  PrimaryParticleEnergy = primaryparticleenergy;
}

/*inline void B4aEventAction::AddVectorScinEnergy(G4double de, G4int fiber) {
    VectorSignals.at(fiber) += de;
}*/
inline void B4aEventAction::AddVectorScinEnergy(G4double de, G4int tower, G4int fiber) {
    VectorSignals.at(320*(tower-1)+fiber) += de;
}
/*inline void B4aEventAction::AddVectorCherPE(G4int fiber, G4int n) {
    VectorSignalsCher.at(fiber) = VectorSignalsCher.at(fiber) + n;
}*/
inline void B4aEventAction::AddVectorCherPE(G4int tower, G4int fiber, G4int n) {
    VectorSignalsCher.at(320*(tower-1)+fiber) = VectorSignalsCher.at(320*(tower-1)+fiber) + n;
}
inline void B4aEventAction::Addem(G4double de) {
  Energyem += de; 
}

inline void B4aEventAction::Addem2(G4double de){
  Energyem2 += de;
}

inline void B4aEventAction::AddScin(G4double de){
  EnergyScin += de;
}

inline void B4aEventAction::AddCher(G4double de){
  EnergyCher += de;
}

inline void B4aEventAction::AddCherenkov(G4int n){
  NofCherenkovDetected = NofCherenkovDetected +n;
}

/*inline void B4aEventAction::AddScintillation(){
  NofScintillationDetected = NofScintillationDetected +1;
}*/

inline void B4aEventAction::Addenergy(G4double de){
  EnergyTot += de;
}
inline void B4aEventAction::AddVectorDepositedEnergy(G4double e, G4int tower){
  VectorDepositedEnergy.at(tower-1) += e;
}
inline void B4aEventAction::AddVectorDepositedEScin(G4double e, G4int tower){
  VectorDepositedEScin.at(tower-1) += e;
}
inline void B4aEventAction::AddVectorDepositedECher(G4double e, G4int tower){
  VectorDepositedECher.at(tower-1) += e;
}

/*inline void B4aEventAction::AddEnergyfibre(G4double de, G4int number){
    Signalfibre[number] += de;
}*/

/*inline void B4aEventAction::AddSignalfibre(G4int number){
    Signalfibre[number] = Signalfibre[number] + 1;
}*/
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 
