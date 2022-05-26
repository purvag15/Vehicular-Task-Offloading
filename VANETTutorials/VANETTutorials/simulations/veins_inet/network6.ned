//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package vanettutorials.simulations.veins_inet;

import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import vanettutorials.veins_inet.VeinsInetCar;
import vanettutorials.veins_inet.VeinsInetEdge;
import vanettutorials.veins_inet.VeinsInetRSU;
import vanettutorials.veins_inet.VeinsInetManager;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.visualizer.contract.IIntegratedVisualizer;

//
// TODO auto-generated type
//
network Network6
{
    submodules:
      
        radioMedium: Ieee80211ScalarRadioMedium;
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,50");
        }
        manager: VeinsInetManager;
        node[0]: VeinsInetCar;
        edge[1]: VeinsInetEdge{
            parameters:
                @display("r=,,#707070;p=2200,1500;i=veins/sign/newedge");
        };
        rsu[1]: VeinsInetRSU{
            parameters:
                @display("r=,,#707070;p=2200,1500;i=veins/sign/rsu_s;is=s");
        };
}
