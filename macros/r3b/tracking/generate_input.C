
void generate_input()
{
    ofstream* ofile = new ofstream("../../../input/fragment_tracker.dat");
    
    Int_t Z = 50;
    Int_t A[] = {128, 129, 130};
    char* mass[] = {(char*)"127.910537", (char*)"128.913483", (char*)"129.913971"};
    Double_t theta, phi;
    for(Int_t i = 0; i < 10000; i++)
    {
        Int_t index = i%3;

        theta = TMath::ACos(gRandom->Uniform(1., TMath::Cos(0.5*TMath::DegToRad())));
        phi = gRandom->Uniform(0., TMath::TwoPi());
        Double_t p = A[index]*1.4;
        Double_t pz = p * TMath::Cos(theta);
        Double_t px = p * TMath::Sin(theta) * TMath::Cos(phi);
        Double_t py = p * TMath::Sin(theta) * TMath::Sin(phi);

        (*ofile) << "   " << i << "   1   0.   0." << endl;
        (*ofile) << "      -1   " << Z << "   " << A[index] << "   "
        << px << "   " << py << "   " << pz << "   0.   0.   3.   " << mass[index] << endl;
    }
    
    ofile->close();
}
