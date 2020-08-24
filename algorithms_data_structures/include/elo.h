#pragma once
#include <tuple>
#include <math.h>

#define KVALUE 32

namespace alg {
	// reference: https://en.wikipedia.org/wiki/Elo_rating_system#Mathematical_details
	// cool video: https://www.youtube.com/watch?v=AsYfbmp0To0

	/* Evaluates the change in elo after a given result (W/L/T)
	* @param elo1: player A's elo rating
	* @param elo2: player B's elo rating
	* @param result: the result of the game according to player A;
	* 1 A wins, 0 B wins, 0.5 tie
	* @return a 2-tuple containing player A and player B's new ratings
	*/
	static std::tuple<double, double> EloEvaluate(double eloA, double eloB, double resultA) {
		double qA = pow(10, eloA / 400);
		double qB = pow(10, eloB / 400);

		double expectedA = qA / (qA + qB);
		double expectedB = qB / (qA + qB);

		// update elos; assuming K = 32
		double newA = eloA + (double)KVALUE * (resultA - expectedA);
		// Note: result B == 1 - resultA
		double newB = eloB + (double)KVALUE * ((1.0 - resultA) - expectedB);

		return std::make_tuple((int)newA, (int)newB);
	}
}