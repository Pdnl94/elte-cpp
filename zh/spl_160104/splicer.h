#ifndef splicer_h_included
#define splicer_h_included

#include <vector>
#include <algorithm>

template<typename T>
class splicer {

	std::vector<T> tarolo;
public:
	template<class MasikTipus>
	void append(MasikTipus& masik) {
		splice(masik, masik.begin(), masik.end());
	}
	
	template<class MasikTipus, class MasikTipusIteratora>
	void splice(MasikTipus& masik, MasikTipusIteratora begin, MasikTipusIteratora end) {
		tarolo.insert(tarolo.end(), begin, end);
		masik.erase(begin, end);
	}

	template<class MasikTipus>
	splicer(MasikTipus& masik) {
		append(masik);
	}
	
	splicer(splicer<T>& masik) {
		append(masik.tarolo);
	}
	
	int size() const {
		return tarolo.size();
	}
	
	const T& get(int index) const {
		return tarolo[index];
	}

	T& get(int index) {
		return tarolo[index];
	}
	
	template<class MasikTipus>
	void operator+=(MasikTipus& masik) {
		append(masik);
	}
	
	void operator-=(const T& elem) {
		tarolo.erase(std::remove(tarolo.begin(), tarolo.end(), elem), tarolo.end());
	}
	
};

#endif // splicer_h_included
