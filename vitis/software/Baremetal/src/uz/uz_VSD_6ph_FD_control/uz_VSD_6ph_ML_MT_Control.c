/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Josef Knoblach
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/


#include "uz_VSD_6ph_ML_MT_Control.h"

/**
 * @brief helper function for get_k_parameter, returns indexes of LUT
 * @param p1 Index of first Phase with OPF
 * @param p2 Index of second Phase with OPF
 * @return int corresponding index in lookup-table for fault-scenario
 */
int get_index_OPF_2(int p1, int p2);

/**
 * @brief helper function for get_k_parameter, returns indexes of LUT
 * @param p1 Index of fist Phase with OPF
 * @param p2 Index of second Phase with OPF
 * @param p3 Index of third Phase with OPF
 * @return int corresponding index in lookup-table for fault-scenario
 */
int get_index_OPF_3(int p1, int p2, int p3);

/**
 * @brief struct for open phases
 *
 */
typedef struct uz_6phFD_opf{
    int opf1;    	/**< phasenumber of 1. opf */
    int opf2;     	/**< phasenumber of 2. opf */
    int opf3;       /**< phasenumber of 3. opf */
    int opf4;       /**< phasenumber of 4. opf */
    int opf5;       /**< phasenumber of 5. opf */
    int opf6;       /**< phasenumber of 6. opf */
    int num_opf;		/**< number of opfs */
}uz_6phFD_opf;


/**
 * @brief helper function: creates struct with number of open phases and indices of faulted phases from uz_6phFD_indices fault-indices struct
 *
 * @param input uz_6phFD_indices struct with fault indices
 * @return uz_6phFD_opf struct with number of opnen phases and orderd indices of faulted phases
 */
uz_6phFD_opf uz_num_opf(uz_6phFD_indices input);


const kparameter k_1OPF_2N_ML[6] = {
	{ -1.000000f , 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.554700f },
	{ -0.250000f , 0.433010f, -0.433010f, 0.750000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.554700f },
	{ -0.250000f , -0.433010f, 0.433010f, 0.750000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.554700f },
	{ 0.750000f , 0.433010f, -0.433010f, -0.250000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.554700f },
	{ 0.750000f , -0.433010f, 0.433010f, -0.250000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.554700f },
	{ 0.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.554700f }
};


const kparameter k_1OPF_2N_MT[6] = {
	{ -1.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ 0.500000f , 0.866030f, -0.866030f, 0.500000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ 0.500000f , -0.866030f, 0.866030f, 0.500000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ 0.500000f , 0.866030f, -0.866030f, 0.500000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ 0.500000f , -0.866030f, 0.866030f, 0.500000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ -1.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f }
};


const kparameter k_2OPF_2N[15] = {
	{ -1.000000f , 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500000f },
	{ -1.000000f , 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500000f },
	{ -1.000000f , 0.000000f, -3.464100f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ -1.000000f , 0.000000f, 3.464100f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ -1.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577351f },
	{ -1.000000f , 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500000f },
	{ 0.500000f , 0.866030f, -0.866030f, 0.500000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ 2.000000f , -1.732050f, -1.732050f, 2.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ -1.000000f , 3.464100f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ 2.000000f , 1.732050f, 1.732050f, 2.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ 0.500000f , -0.866030f, 0.866030f, 0.500000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ -1.000000f , -3.464100f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ 1.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500000f },
	{ 1.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500001f },
	{ 1.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500000f }
};


const kparameter k_3OPF_2N[2] = {
	{ -1.000000f , 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500000f },
	{ 0.999990f , 0.000000f, 0.000000f, -0.999990f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500001f }
};


const kparameter k_1OPF_1N_ML[6] = {
	{ -0.666820f , 0.000480f, -0.002870f, -0.001440f, -0.333180f, -0.000480f, 0.333180f, 0.000480f, 0.542257f },
	{ -0.166450f , 0.289070f, -0.289170f, 0.499500f, 0.166350f, -0.288910f, -0.166350f, 0.288910f, 0.541780f },
	{ -0.166580f , -0.288880f, 0.288640f, 0.500000f, 0.166740f, 0.288570f, -0.166740f, -0.288570f, 0.541819f },
	{ 0.500190f , 0.289220f, -0.287740f, -0.166980f, 0.288980f, 0.166040f, -0.288980f, -0.166040f, 0.541659f },
	{ 0.499690f , -0.288170f, 0.288310f, -0.167820f, -0.289120f, 0.166530f, 0.289120f, -0.166530f, 0.541670f },
	{ 0.003220f , -0.001720f, -0.004520f, -0.669750f, 0.004520f, -0.330250f, -0.004520f, 0.330250f, 0.542072f }
};


const kparameter k_2OPF_1N_ML[15] = {
	{ -0.833480f , 0.288740f, -0.288420f, 0.499890f, -0.166520f, -0.288740f, 0.166520f, 0.288740f, 0.493160f },
	{ -0.833420f , -0.288700f, 0.288520f, 0.499960f, -0.166580f, 0.288700f, 0.166580f, -0.288700f, 0.493219f },
	{ -0.992460f , -0.090120f, -3.466120f, -0.975850f, -0.007540f, 0.090120f, 0.007540f, -0.090120f, 0.284537f },
	{ -0.177490f , -0.220420f, 0.394440f, -0.177390f, -0.822510f, 0.220420f, 0.822510f, -0.220420f, 0.481952f },
	{ -0.749680f , 0.250970f, 0.250320f, -0.749030f, -0.250320f, -0.250970f, 0.250320f, 0.250970f, 0.526924f },
	{ -0.333390f , 0.000260f, 0.000000f, 1.000000f, 0.333300f, 0.000130f, -0.333300f, -0.000130f, 0.493167f },
	{ 0.374730f , 0.899330f, -0.398500f, 0.375710f, 0.342250f, -0.090980f, -0.342250f, 0.090980f, 0.526942f },
	{ 1.952220f , -1.793020f, -1.779830f, 1.939030f, -0.065260f, -0.083280f, 0.065260f, 0.083280f, 0.284383f },
	{ -0.176870f , 0.393700f, -0.220560f, -0.177290f, 0.220560f, -0.822710f, -0.220560f, 0.822710f, 0.482021f },
	{ 0.354510f , 0.086410f, 0.086560f, 0.354360f, 0.602290f, 0.602340f, -0.602290f, -0.602340f, 0.482049f },
	{ 0.375200f , -0.398800f, 0.899460f, 0.374810f, -0.091360f, 0.342030f, 0.091360f, -0.342030f, 0.527005f },
	{ -0.976640f , -3.472780f, -0.087200f, -0.967620f, 0.087200f, -0.032380f, -0.087200f, 0.032380f, 0.285153f },
	{ 1.000000f , 0.000000f, 0.000000f, -0.333360f, 0.000000f, 0.333320f, 0.000000f, -0.333320f, 0.493198f },
	{ 0.500030f , 0.289060f, -0.288660f, -0.833110f, 0.288660f, -0.166890f, -0.288660f, 0.166890f, 0.493145f },
	{ 0.499400f , -0.288760f, 0.289020f, -0.833280f, -0.289020f, -0.166720f, 0.289020f, 0.166720f, 0.493153f }
};


const kparameter k_1OPF_1N_MT[6] = {
	{ -0.641110f , -0.208910f, -0.754240f, -0.295480f, -0.358890f, 0.208910f, 0.358890f, -0.208910f, 0.694444f },
	{ 0.297470f , -0.212340f, -0.750800f, 0.643090f, -0.001470f, -0.415260f, 0.001470f, 0.415260f, 0.694443f },
	{ -0.174810f , -1.023460f, 0.060320f, 0.170830f, 0.360360f, 0.206350f, -0.360360f, -0.206350f, 0.694444f },
	{ 0.170830f , 0.060320f, -1.023460f, -0.174800f, 0.206350f, 0.360360f, -0.206350f, -0.360360f, 0.694444f },
	{ 0.643150f , -0.750600f, -0.212220f, 0.297360f, -0.415160f, -0.001360f, 0.415160f, 0.001360f, 0.694398f },
	{ -0.295480f , -0.754230f, -0.208900f, -0.641110f, 0.208900f, -0.358890f, -0.208900f, 0.358890f, 0.694444f }
};


const kparameter k_2OPF_1N_MT[15] = {
	{ -0.535290f , 0.268580f, -0.804910f, 0.534810f, -0.464710f, -0.268580f, 0.464720f, 0.268570f, 0.557675f },
	{ -1.000200f , -0.534990f, -0.000340f, 0.073370f, 0.000200f, 0.534990f, -0.000200f, -0.534990f, 0.557664f },
	{ -1.000000f , 0.000000f, -3.464100f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ 0.000000f , -0.267950f, -0.267940f, 0.000000f, -1.000000f, 0.267950f, 1.000000f, -0.267950f, 0.557676f },
	{ -1.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ -0.078840f , -0.533980f, 0.000000f, 1.000000f, 0.460580f, -0.266990f, -0.460580f, 0.266990f, 0.557672f },
	{ 0.500000f , 0.866030f, -0.866030f, 0.500000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ 2.000000f , -1.732050f, -1.732050f, 2.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ 0.000000f , -0.267950f, -0.267950f, 0.000000f, 0.267950f, -1.000000f, -0.267950f, 1.000000f, 0.557677f },
	{ 0.000000f , -0.267940f, -0.267950f, 0.000000f, 0.732050f, 0.732050f, -0.732050f, -0.732050f, 0.557677f },
	{ 0.500000f , -0.866030f, 0.866030f, 0.500000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.577350f },
	{ -1.000000f , -3.464100f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.288675f },
	{ 1.000000f , 0.000000f, -0.534990f, -0.075160f, -0.267500f, 0.462420f, 0.267500f, -0.462420f, 0.557677f },
	{ 0.071860f , 0.000000f, -0.535860f, -1.000000f, 0.535860f, 0.000000f, -0.535860f, 0.000000f, 0.557675f },
	{ 0.543660f , -0.796040f, 0.263470f, -0.540410f, -0.263470f, -0.459590f, 0.263470f, 0.459590f, 0.557668f }
};


const kparameter k_3OPF_1N[20] = {
	{ -1.000000f , 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500000f },
	{ 1.365510f , 1.365740f, -4.097200f, -1.365590f, -2.365420f, -1.365740f, 2.365220f, 1.365630f, 0.122035f },
	{ 0.732050f , -1.000000f, -2.999990f, 2.732040f, -1.732050f, 0.999990f, 1.732050f, -1.000000f, 0.149430f },
	{ -1.000000f , 0.732050f, 0.000000f, -0.267950f, 0.000000f, -0.732050f, 0.000000f, 0.732050f, 0.408248f },
	{ -2.732040f , -1.000000f, -2.999980f, -0.732050f, 1.732040f, 1.000000f, -1.732050f, -1.000000f, 0.149430f },
	{ -0.366020f , -0.366030f, 1.098080f, 0.366020f, -0.633980f, 0.366030f, 0.633970f, -0.366020f, 0.408249f },
	{ -1.000010f , -2.731990f, 0.000000f, -3.731940f, 0.000000f, 2.731990f, 0.000000f, -2.731950f, 0.122011f },
	{ 1.000000f , 0.000000f, -4.000000f, -0.999950f, -2.000000f, 0.000020f, 2.000000f, -0.000030f, 0.149430f },
	{ -3.731980f , -0.000230f, -2.732010f, -1.000130f, 2.731990f, 0.000220f, -2.732010f, -0.000140f, 0.122010f },
	{ -0.267950f , 0.000000f, 0.732050f, -1.000000f, -0.732050f, 0.000000f, 0.732050f, 0.000000f, 0.408249f },
	{ 0.267950f , 0.732050f, 0.000000f, 1.000000f, 0.633980f, 0.366030f, -0.633970f, -0.366020f, 0.408249f },
	{ 3.731970f , -2.732010f, 0.000000f, 1.000000f, 2.365980f, -1.366000f, -2.365960f, 1.366000f, 0.122011f },
	{ -0.999990f , -4.000000f, 0.000000f, 1.000000f, 0.000000f, -2.000000f, 0.000000f, 2.000000f, 0.149429f },
	{ 1.000010f , 0.000010f, -2.732010f, 3.731960f, -1.365990f, 2.365970f, 1.366000f, -2.365990f, 0.122011f },
	{ 0.366030f , 1.098080f, -0.366020f, -0.366020f, 0.366030f, -0.633970f, -0.366030f, 0.633970f, 0.408248f },
	{ 2.732040f , -2.999990f, -0.999990f, 0.732050f, 1.000000f, -1.732050f, -0.999990f, 1.732050f, 0.149430f },
	{ 1.000000f , 0.000000f, 0.732050f, 0.267950f, 0.366020f, 0.633970f, -0.366030f, -0.633970f, 0.408249f },
	{ -0.732070f , -2.999950f, -1.000010f, -2.732020f, 1.000000f, 1.732040f, -1.000010f, -1.732020f, 0.149430f },
	{ -1.366010f , -4.098050f, 1.366020f, 1.366010f, -1.366010f, -2.366000f, 1.366020f, 2.366010f, 0.122009f },
	{ 1.000000f , 0.000000f, 0.000000f, -1.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.500000f }
};



kparameter get_k_parameter(uz_6phFD_indices input, int N1N2, int ML){

uz_6phFD_opf helpstruct;
helpstruct = uz_num_opf(input);

int p1 = helpstruct.opf1;
int p2 = helpstruct.opf2;
int p3 = helpstruct.opf3;
int num_OPF = helpstruct.num_opf;

//check input values
kparameter k = {0};
int i = 0;

kparameter k_error = {0};

// check parameter:

if(num_OPF == 0){
	k.a = 1.0f;
	return k;
}

if(N1N2 == 2){
    if(num_OPF == 1){
            if(ML){
                k = k_1OPF_2N_ML[p1-1];
            }
            else{   //MT
                k = k_1OPF_2N_MT[p1-1];
            }
    }
    else if(num_OPF == 2){
    	i = get_index_OPF_2(p1, p2);
        k = k_2OPF_2N[i];
    }
    else if(num_OPF == 3){
        if( (p1 == 1) && (p2 == 2) && (p3 == 3) ){
            k = k_3OPF_2N[0];
        }
        else if( (p1 == 4) && (p2 == 5) && (p3 == 6) ){
            k = k_3OPF_2N[1];
        }
    }
    else{
        // more than 3 OPF
        k = k_error;
    }

}
else if( N1N2 ==1){
    if( num_OPF == 1){
            if(ML){
                k = k_1OPF_1N_ML[p1-1];
            }
            else{   //MT
                k = k_1OPF_1N_MT[p1-1];
            }
    }
    else if(num_OPF == 2){
            if(ML){
            	i =get_index_OPF_2(p1, p2);
                k = k_2OPF_1N_ML[i];
            }
            else{   //MT
            	i = get_index_OPF_2(p1, p2);
                k = k_2OPF_1N_MT[i];
            }
    }
    else if(num_OPF == 3){
    			i = get_index_OPF_3(p1,p2,p3);
                k = k_3OPF_1N[i];
    }
    else{
        // more than 3 OPF
        k = k_error;
    }

}
return k;
}




int get_index_OPF_2(int p1, int p2){
    int index = 0;

        if(p1 == 1){
             if(p2 == 2){
                    index = 0;   // 1-2
            }
            else if (p2 == 3){
                    index = 1;   // 1-3
            }
            else if(p2 == 4){
                    index = 2;   // 1-4
            }
            else if(p2 == 5){
                    index = 3;   // 1-5
            }
            else if(p2 == 6){
                    index = 4;   // 1-6
            }
        }
        else if(p1 == 2){
            if(p2 == 3){
                    index = 5;   // 2-3
            }
            else if(p2 == 4){
                    index = 6;   // 2-4
            }
            else if(p2 == 5){
                    index = 7;   // 2-5
            }
            else if(p2 == 6){
                    index = 8;   // 2-6
            }
        }
        else if(p1 == 3){
            if(p2 == 4){
                    index = 9;   // 3-4
            }
            else if(p2 == 5){
                    index = 10;  // 3-5
            }
            else if (p2 == 6){
                    index = 11;  // 3-6
            }
        }
        else if(p1 == 4){
            if(p2 == 5){
                    index = 12;  // 4-5
            }
            else if(p2 == 6){
                    index = 13;  // 4-6
            }
        }
        else if (p1 == 5 && p2 == 6){   // 5-6
                    index = 14;
        }
    return index;
}

int get_index_OPF_3(int p1, int p2, int p3){
    int index = 0;

        if(p1 == 1){
             if(p2 == 2){
                    if(p3 == 3){
                            index = 0;   // 1-2-3
                    }
                    else if(p3 == 4){
                            index = 1;   // 1-2-4
                    }
                    else if(p3 == 5){
                            index = 2;   // 1-2-5
                    }
                    else if(p3 == 6){
                            index = 3;   // 1-2-6
                    }
            }
            else if (p2 == 3){
                    if(p3 == 4){
                            index = 4;   // 1-3-4
                    }
                    else if(p3 == 5){
                            index = 5;   // 1-3-5
                    }
                    else if(p3 == 6){
                            index = 6;   // 1-3-6
                    }
            }
            else if(p2 == 4){
                    if(p3 == 5){
                            index = 7;   // 1-4-5
                    }
                    else if(p3 == 6){
                            index = 8;   // 1-4-6
                    }
            }
            else if((p2 == 5) && (p3 == 6)){
                            index = 9;  // 1-5-6
            }
        }
        else if(p1 == 2){
            if(p2 == 3){
                    if(p3 == 4){
                            index = 10;   // 2-3-4
                    }
                    else if(p3 == 5){
                            index = 11;   // 2-3-5
                    }
                    else if(p3 == 6){
                            index = 12;   // 2-3-6
                    }
            }
            else if(p2 == 4){
                    if(p3 == 5){
                            index = 13;   // 2-4-5
                    }
                    else if(p3 == 6){
                            index = 14;   // 2-4-6
                    }
            }
            else if((p2 == 5)&& (p3 == 6) ){
                            index = 15;   // 2-5-6
            }
        }
        else if(p1 == 3){
            if(p2 == 4){
                    if(p3 == 5){
                            index = 16;  // 3-4-5
                    }
                    else if (p3 == 6){
                            index = 17;  // 3-4-6
                    }
            }
            else if((p2 == 5) && (p3 == 6) ){
                            index = 18;  // 3-5-6
            }
        }
        else if((p1 == 4) && (p2 == 5) && (p3 == 6) ) {
            if(p2 == 5){
                            index = 19;  // 4-5-6
            }
        }
    return index;
}




uz_6phFD_opf uz_num_opf(uz_6phFD_indices input){

	uz_6phFD_opf output;

	int opf_phases[6] = {0};
	int num_OPF = 0;

	if (input.R1 == 1){
		opf_phases[num_OPF] = 1;
		num_OPF += 1;
	}
	if (input.R2 == 1){
		opf_phases[num_OPF] = 2;
		num_OPF += 1;
	}
	if (input.R3 == 1){
		opf_phases[num_OPF] = 3;
		num_OPF += 1;
	}
	if (input.R4 == 1){
		opf_phases[num_OPF] = 4;
		num_OPF += 1;
	}
	if (input.R5 == 1){
		opf_phases[num_OPF] = 5;
		num_OPF += 1;
	}
	if (input.R6 == 1){
		opf_phases[num_OPF] = 6;
		num_OPF += 1;
	}
	output.opf1 = opf_phases[0];
	output.opf2 = opf_phases[1];
	output.opf3 = opf_phases[2];
	output.opf4 = opf_phases[3];
	output.opf5 = opf_phases[4];
	output.opf6 = opf_phases[5];
	output.num_opf = num_OPF;
	return output;

}