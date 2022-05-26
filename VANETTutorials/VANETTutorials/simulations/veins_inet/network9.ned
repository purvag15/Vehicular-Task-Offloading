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

import vanettutorials.veins_inet.VeinsInetCar;
import vanettutorials.veins_inet.VeinsInetCar1;
import vanettutorials.veins_inet.VeinsInetEdge1;
import vanettutorials.veins_inet.VeinsInetRSU1;
import vanettutorials.veins_inet.VeinsInetManager;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

network Network9
{
    submodules:

        radioMedium: Ieee80211ScalarRadioMedium;
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,50");
        }
        manager: VeinsInetManager;
        node[0]: VeinsInetCar1;
        //        node[1]: VeinsInetCar1;
        edge[3]: VeinsInetEdge1 {
            parameters:
                @display("r=,,#707070;p=2089,1452;i=veins/sign/newedge");
        }
        rsu[3]: VeinsInetRSU1 {
            parameters:
                @display("r=,,#707070;p=2021,1483;i=veins/sign/rsu_s;is=s");
        }
        meco[1]: VeinsInetEdge1 {
            parameters:
                @display("r=,,#707070;p=1479,1394;i=veins/sign/newedge");
        }
}
