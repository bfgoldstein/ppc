//
// ./copyright
//
// INTEL CONFIDENTIAL 
//
// Copyright 2011 Intel Corporation All Rights Reserved.  
//
// The source code contained or described herein and all documents related to the 
// source code ("Material") are owned by Intel Corporation or its suppliers
// or licensors. Title to the Material remains with Intel Corporation or its suppliers 
// and licensors. The Material contains trade secrets and proprietary and confidential 
// information of Intel or its suppliers and licensors. The Material is protected by 
// worldwide copyright and trade secret laws and treaty provisions. No part of the 
// Material may be used, copied, reproduced, modified, published, uploaded, posted,
// transmitted, distributed, or disclosed in any way without Intel.s prior express 
// written permission.
//
// No license under any patent, copyright, trade secret or other intellectual property 
// right is granted to or conferred upon you by disclosure or delivery of the Materials, 
// either expressly, by implication, inducement, estoppel or otherwise. Any license under 
// such intellectual property rights must be express and approved by Intel in writing.
//
//
#include <stdio.h>
#include <sys/time.h>
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

const int RAND_N = 1 << 18;
static const float RISKFREE = 0.06;
static const float VOLATILITY = 0.10;

union FPARRAY {
	float *SPData;
	double *DPData;
};

template<class Basetype>
Basetype cdfnorminv(Basetype P) {
	const Basetype a1 = 2.50662823884;
	const Basetype a2 = -18.61500062529;
	const Basetype a3 = 41.39119773534;
	const Basetype a4 = -25.44106049637;
	const Basetype b1 = -8.4735109309;
	const Basetype b2 = 23.08336743743;
	const Basetype b3 = -21.06224101826;
	const Basetype b4 = 3.13082909833;
	const Basetype c1 = 0.337475482272615;
	const Basetype c2 = 0.976169019091719;
	const Basetype c3 = 0.160797971491821;
	const Basetype c4 = 2.76438810333863E-02;
	const Basetype c5 = 3.8405729373609E-03;
	const Basetype c6 = 3.951896511919E-04;
	const Basetype c7 = 3.21767881768E-05;
	const Basetype c8 = 2.888167364E-07;
	const Basetype c9 = 3.960315187E-07;
	Basetype y, z;

	if (P <= 0 || P >= 1.0) {
		printf("MoroInvCND(): bad parameter\n");
	}

	y = P - 0.5;
	if (fabs(y) < 0.42) {
		z = y * y;
        z = y * (((a4 * z + a3) * z + a2) * z + a1) / ((((b4 * z + b3) * z + b2) * z + b1) * z + 1);
	} else {
		if (y > 0)
			z = log(-log(1.0 - P));
		else
			z = log(-log(P));

        z = c1 + z * (c2 + z * (c3 + z * (c4 + z * (c5 + z * (c6 + z * (c7 + z * (c8 + z * c9)))))));
		if (y < 0)
			z = -z;
	}

	return z;
}

void MonteCarlo(float *h_CallResult, float *h_CallConfidence, float *S,
		float *X, float *T, int OPT_N) {
	float l_Random[RAND_N];
	for (int k = 0; k < RAND_N; k++)
		l_Random[k] = cdfnorminv<float>((k + 1.0) / (RAND_N + 1.0));

	for (int opt = 0; opt < OPT_N; opt++) {
		float VBySqrtT = VOLATILITY * sqrt(T[opt]);
		float MuByT = (RISKFREE - 0.5 * VOLATILITY * VOLATILITY) * T[opt];
		float Sval = S[opt];
		float Xval = X[opt];
		float val = 0.0, val2 = 0.0;

		for (int pos = 0; pos < RAND_N; pos++) {
			float callValue =
					max(0.0, Sval *exp(MuByT + VBySqrtT * l_Random[pos]) - Xval);
			val += callValue;
			val2 += callValue * callValue;
		}

		float exprt = expf(-RISKFREE * T[opt]);
		h_CallResult[opt] = exprt * val / (float) RAND_N;
		float stdDev = sqrtf(
				((float) RAND_N * val2 - val * val)
						/ ((float) RAND_N * (float) (RAND_N - 1)));
		h_CallConfidence[opt] = (float) (exprt * 1.96 * stdDev
				/ sqrtf((float) RAND_N));
	} //end of for
}
