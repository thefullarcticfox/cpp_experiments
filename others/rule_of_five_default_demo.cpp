#include <utility>

struct trivial {
	trivial() = default;
	trivial(const trivial&) = default;
	trivial(trivial&&) = default;
	trivial&	operator=(const trivial&) = default;
	trivial&	operator=(trivial&&) = default;
	~trivial() = default;
};

struct nontrivial {
	nontrivial();
};

nontrivial::nontrivial() = default;       // not first declaration

int		main() {
	trivial		a;
	trivial		acopy(a);
	trivial		amove(std::move(a));
	nontrivial	b;

	trivial		acopyassign;
	trivial		amoveassign;

	acopyassign = acopy;
	amoveassign = std::move(amove);

	(void)acopyassign;
	(void)amoveassign;

}
