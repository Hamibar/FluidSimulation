#include "Simulation.h"

void Simulation::makeStep(Fluid& fl, float dt) { //  2 - 0 // 1 - 1
	if (fl.size() < 2) { return; }
	diffuse(fl, fl.vx0, fl.vx, 5, fl.viscosity, 'x', dt);
	diffuse(fl, fl.vy0, fl.vy, 5, fl.viscosity, 'y', dt);

	project(fl, fl.vx0, fl.vy0, fl.vx, fl.vy, 5);

	advect(fl, fl.vx0, fl.vy0, fl.vx, fl.vx0, 'x', dt);
	advect(fl, fl.vx0, fl.vy0, fl.vy, fl.vy0, 'y', dt);
	
	project(fl, fl.vx, fl.vy, fl.vx0, fl.vy0, 5);

	diffuse(fl, fl.density0, fl.density, 5, fl.diffusion, '0', dt);
	advect(fl, fl.vx, fl.vy, fl.density, fl.density0, '0', dt);
}

void Simulation::solve(Fluid& fl, mtxFl& par, mtxFl& par0, int iter_count, float a, float c, char axis) { 
	for (int k = 0; k < iter_count; ++k) {
		for (int x = 1; x < fl.size() - 1; ++x) {
			for (int y = 1; y < fl.size() - 1; ++y) {
				par[x][y] = (par0[x][y] + a * (par[x + 1][y] + par[x - 1][y] + par[x][y + 1] + par[x][y - 1])) / c;
			}
		}
	}
	handleBorder(fl, par, axis);
}

void Simulation::diffuse(Fluid& fl, mtxFl& par, mtxFl& par0, int iter_count, float diff, char axis, float dt) {
	float a = dt * diff * (fl.size() - 2) * (fl.size() - 2);
	solve(fl, par, par0, iter_count, a, 1 + 4 * a, axis);
}

void Simulation::advect(Fluid& fl, mtxFl& vx, mtxFl& vy, mtxFl& d, mtxFl& d0, char axis, float dt) {
	float i0, i1, j0, j1;

	float dtx = dt * (fl.size() - 2);
	float dty = dt * (fl.size() - 2);

	for (int j = 1; j < fl.size() - 1; j++) {
		for (int i = 1; i < fl.size() - 1; i++) {
			float x = i  - (dtx * vx[i][j]);
			if (x < 0.5f) x = 0.5f;
			if (x > fl.size() + 0.5f) x = fl.size() + 0.5f;
			i0 = floor(x);
			i1 = i0 + 1.0f;

			float y = j - (dty * vy[i][j]);
			if (y < 0.5f) y = 0.5f;
			if (y > fl.size() + 0.5f) y = fl.size() + 0.5f;
			j0 = floor(y);
			j1 = j0 + 1.0f;

			float s1 = x - i0;
			float s0 = 1.0f - s1;
			float t1 = y - j0;
			float t0 = 1.0f - t1;

			int i0i = int(i0);
			int i1i = int(i1);
			int j0i = int(j0);
			int j1i = int(j1);

			if (i0i >= fl.size()) { i0i = fl.size() - 1; }
			if (i1i >= fl.size()) { i1i = fl.size() - 1; }
			if (j0i >= fl.size()) { j0i = fl.size() - 1; }
			if (j1i >= fl.size()) { j1i = fl.size() - 1; }

			d[i][j] =
				s0 * (t0 * d0[i0i][j0i] + t1 * d0[i0i][j1i]) +
				s1 * (t0 * d0[i1i][j0i] + t1 * d0[i1i][j1i]);
		}
	}
	handleBorder(fl, d, axis);
}

void Simulation::project(Fluid& fl, mtxFl& vx, mtxFl& vy, mtxFl& p, mtxFl& div, int iter_count) {
	for (int x = 1; x < fl.size() - 1; ++x) {
		for (int y = 1; y < fl.size() - 1; ++y) {
			div[x][y] = -0.5f * (vx[x + 1][y] - vx[x - 1][y] + vy[x][y + 1] - vy[x][y - 1]) / fl.size();
			p[x][y] = 0;
		}
	}
	handleBorder(fl, div, '0');
	handleBorder(fl, p, '0');
	solve(fl, p, div, iter_count, 1, 4, -1);
	for (int x = 1; x < fl.size() - 1; ++x) {
		for (int y = 1; y < fl.size() - 1; ++y) {
			vx[x][y] -= 0.5f * (p[x+1][y] - p[x-1][y]) * fl.size();
			vy[x][y] -= 0.5f * (p[x][y+1] - p[x][y-1]) * fl.size();
		}
	}
	handleBorder(fl, vx, 'x');
	handleBorder(fl, vy, 'y');
}

void Simulation::handleBorder(Fluid& fl, mtxFl& par, char axis) {
	for (int y = 1, x = 1; x < fl.size() - 1; ++x, ++y) {
		par[x][0] = (axis == 'y' ? -par[x][1] : par[x][1]);
		par[x][fl.size() - 1] = (axis == 'y' ? -par[x][fl.size() - 2] : par[x][fl.size() - 2]);

		par[0][y] = (axis == 'x' ? -par[1][y] : par[1][y]);
		par[fl.size() - 1][y] = (axis == 'x' ? -par[fl.size() - 2][y] : par[fl.size() - 2][y]);

	}
	par[0][0] = 0.5f * (par[0][1] + par[1][0]);
	par[0][fl.size() - 1] = 0.5f * (par[0][fl.size() - 2] + par[1][fl.size() - 1]);  
	par[fl.size() - 1][0] = 0.5f * (par[fl.size() - 2][0] + par[fl.size() - 1][1]);  
	par[fl.size() - 1][fl.size() - 1] = 0.5f * (par[fl.size() - 2][fl.size() - 1] + par[fl.size() - 1][fl.size() - 2]);
}
