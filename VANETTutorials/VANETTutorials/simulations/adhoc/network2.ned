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

package vanettutorials.simulations.adhoc;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.aodv.AodvRouter;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;
//
// TODO auto-generated type
//
network Network2
{
        @display("bgb=939.89996,581.1");
    submodules:
        host1: AodvRouter {
            @display("p=239.148,74.897995");
        }
        host2: AodvRouter {
            @display("p=483,221");
        }
        host3: AodvRouter {
            @display("p=513.774,345.582");
        }
        host4: AodvRouter {
            @display("p=304.848,182.646;b=7,5");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,50");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=50,100");
        }
        visualizer: IntegratedCanvasVisualizer {
            @display("p=50,150");
        }
}
