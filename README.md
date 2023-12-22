# TableAndChairsUE5

Open the ".uproject" file for starting up the editor.

The project has been conducted using both C++ for procedural generation and Blueprint for user input / GUI management.

For table and chairs  parameters randomization several constraint have been set up.

Table:

* 	Htlegs : Table legs height : [80.0, 120.0]
* 	Wttop : Table top width : [200.0, 800.0]
* 	Lttop : Table top length : [200.0, 800.0]
* 	Httop : Table top height : [10.0, 30.0]

Chair:

* 	Wseat : Chair seat width : [30.0, 120.0]
* 	Lseat : Chair seat length : [30.0, 120.0]
* 	Hseat : Chair seat height : [5.0, 20.0]
* 	Hlegs : Chair legs height : [60.0, (HTlegs - HTlegs / 3) - Hseat]
* 	Hback : Chair back height : [30.0, 100.0]


The fixed parameters (table legs width and length, chair legs width and length, back width ) have been hardcoded to 5.0.
Back length is fixes to chair width 