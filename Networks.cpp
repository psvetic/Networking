// A program for determining if an IP address will be routed through a specific port.

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <bitset>

using namespace std;


struct IP{
    unsigned int ipv4_octals[4];
    string ipv4_bin[4];
    char dots[3];
    string port;
};

int main()
{
    int n;
    cout << "How many IP addresses would you like to input? " << endl;
    cin >> n;
    IP IP_array[n];

    for(int i=0;i<n;i++){
        cout << "Enter your " << i+1 << ". IP address: " << endl;
        if(i==0)
            cout << "Format is 000.000.000.000" << endl;
        cin >> IP_array[i].ipv4_octals[0] >> IP_array[i].dots[0]
            >> IP_array[i].ipv4_octals[1] >> IP_array[i].dots[1]
            >> IP_array[i].ipv4_octals[2] >> IP_array[i].dots[2]
            >> IP_array[i].ipv4_octals[3];
    }

    //this is where the MAGIC happens
    for(int j=0;j<n;j++){
        for(int k=0;k<4;k++){
            bitset <8> bin(IP_array[j].ipv4_octals[k]);
            IP_array[j].ipv4_bin[k] = bin.to_string();
            //cout << IP_array[j].ipv4_bin[k] << " ";
        }
        //cout << endl;
    }

    //TABLE
    int m;
    cout << "How many subnet addresses do you want? " << endl;
    cin >> m;

    IP subnetAddress[m+1];

    int cidr[m];
    char slash;

    string exitPort[m+1];

    for(int i=0;i<m;i++){
        cout << "Enter your " << i+1 << ". subnet address: " << endl;
        cin >> subnetAddress[i].ipv4_octals[0] >> subnetAddress[i].dots[0]
            >> subnetAddress[i].ipv4_octals[1] >> subnetAddress[i].dots[1]
            >> subnetAddress[i].ipv4_octals[2] >> subnetAddress[i].dots[2]
            >> subnetAddress[i].ipv4_octals[3];
        cout << "Enter CIDR prefix (e.g. /25): " << endl;
        cin >> slash >> cidr[i];
        cout << cidr[i] << endl;
        cout << "Enter the name/number of the exit port (e.g. rout1)." << endl;
        cout << "Note that 'rout0' is already taken because it is the default port." << endl;
        cin >> exitPort[i];
    }

    for(int j=0;j<m;j++){
        for(int k=0;k<4;k++){
            bitset <8> bin(subnetAddress[j].ipv4_octals[k]);
            subnetAddress[j].ipv4_bin[k] = bin.to_string();
            //cout << subnetAddress[j].ipv4_bin[k] << " ";
        }
        //cout << endl;
    }

    subnetAddress[m].ipv4_bin[0] = "Default";
    exitPort[m] = "rout0";


    //THE FUN PART
    cout << endl;
    int x, y;
    for(int i=0;i<n;i++)
    { // za sve korisnikove adrese
        for(int j=0;j<m;j++)
        { // za sve adrese u tablici
            x = cidr[j] / 8;
            y = cidr[j] % 8;
            if (x == 1)
            {
                if((IP_array[i].ipv4_bin[0] == subnetAddress[j].ipv4_bin[0])
                  && (IP_array[i].ipv4_bin[1].substr(0,y) == subnetAddress[j].ipv4_bin[1].substr(0,y)))
                {
                    IP_array[i].port = exitPort[j];
                    break;
                }
                else
                {
                    IP_array[i].port = exitPort[m];
                }
            }
            else if (x == 2)
            {
                if((IP_array[i].ipv4_bin[0] == subnetAddress[j].ipv4_bin[0])
                  && (IP_array[i].ipv4_bin[1] == subnetAddress[j].ipv4_bin[1])
                  && (IP_array[i].ipv4_bin[2].substr(0,y) == subnetAddress[j].ipv4_bin[2].substr(0,y)))
                {
                    IP_array[i].port = exitPort[j];
                    break;
                }
                else
                {
                    IP_array[i].port = exitPort[m];
                }
            }
            else if (x == 3)
            {
                if((IP_array[i].ipv4_bin[0] == subnetAddress[j].ipv4_bin[0])
                  && (IP_array[i].ipv4_bin[1] == subnetAddress[j].ipv4_bin[1])
                  && (IP_array[i].ipv4_bin[2] == subnetAddress[j].ipv4_bin[2])
                  && (IP_array[i].ipv4_bin[3].substr(0,y) == subnetAddress[j].ipv4_bin[3].substr(0,y)))
                {
                    IP_array[i].port = exitPort[j];
                    break;
                }
                else
                {
                    IP_array[i].port = exitPort[m];
                }
            }
        }
        cout << "The exit port of your " << i+1 << ". address is: " << IP_array[i].port << endl;
    }




    return 0;
}
