#include "Entidad.h"

bool Entidad::colisiona(Entidad *otraEntidad) {
	std::list<Forma> formas1 = getFormas();
	std::list<Forma> formas2 = otraEntidad->getFormas();

	for (auto it1 = formas1.begin(); it1 != formas1.end(); it1++) {
		for (auto it2 = formas2.begin(); it2 != formas2.end(); it2++) {
			if ((*it1).colisiona(*it2)) {
				return true;
			}
		}
	}

	return false;
}
