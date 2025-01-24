#include "Results.h"

Results Results::readResults(const std::string& filename) {
	std::ifstream results_file(filename);
	Results results;
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
	}
	return results;
}

void Results::saveResults(const std::string& filename) const {
	if (save) {
		std::ofstream results_file(filename);
		results_file << results.size();
		for (const auto& result : results) {
			results_file << '\n' << result.first << ' ' << result.second;
		}
		results_file.close();
	}	
}

std::pair<size_t, Results::ResultValue> Results::popResult() {
	if (results.empty()) {
		std::cout << "no results!";
		return { 0, NO_RESULT };
	}
	auto result = results.front();
	results.pop_front();
	return result;
}