#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * pRNG based on http://www.cs.wm.edu/~va/software/park/park.html
 */
#define MODULUS    2147483647
#define MULTIPLIER 48271
#define DEFAULT    123456789

static long seed = DEFAULT;

double Random(void)
/* ----------------------------------------------------------------
 * Random returns a pseudo-random real number uniformly distributed 
 * between 0.0 and 1.0. 
 * ----------------------------------------------------------------
 */
{
  const long Q = MODULUS / MULTIPLIER;
  const long R = MODULUS % MULTIPLIER;
        long t;

  t = MULTIPLIER * (seed % Q) - R * (seed / Q);
  if (t > 0) 
    seed = t;
  else 
    seed = t + MODULUS;
  return ((double) seed / MODULUS);
}

/*
 * End of the pRNG algorithm
 */

typedef struct {
    double x, y, z;
    double mass;
    } Particle;
typedef struct {
    double xold, yold, zold;
    double fx, fy, fz;
    } ParticleV;

void InitParticles( Particle[], ParticleV [], int );
double ComputeForces( Particle [], Particle [], ParticleV [], int );
double ComputeNewPos( Particle [], ParticleV [], int, double);

int main()
{
    double time;
    Particle  * particles;   /* Particles */
    ParticleV * pv;          /* Particle velocity */
    int         npart, i, j;
    int         cnt;         /* number of times in loop */
    double      sim_t;       /* Simulation time */
    int tmp;
    tmp = fscanf(stdin,"%d\n",&npart);
    tmp = fscanf(stdin,"%d\n",&cnt);
/* Allocate memory for particles */
    particles = (Particle *) malloc(sizeof(Particle)*npart);
    pv = (ParticleV *) malloc(sizeof(ParticleV)*npart);
/* Generate the initial values */
    InitParticles( particles, pv, npart);
    sim_t = 0.0;

    while (cnt--) {
      double max_f;
      /* Compute forces (2D only) */
      max_f = ComputeForces( particles, particles, pv, npart );
      /* Once we have the forces, we compute the changes in position */
      sim_t += ComputeNewPos( particles, pv, npart, max_f);
    }
    for (i=0; i<npart; i++)
      fprintf(stdout,"%.5lf %.5lf %.5lf\n", particles[i].x, particles[i].y, particles[i].z);
    return 0;
}

void InitParticles( Particle particles[], ParticleV pv[], int npart )
{
    int i;
    for (i=0; i<npart; i++) {
	particles[i].x	  = Random();
	particles[i].y	  = Random();
	particles[i].z	  = Random();
	particles[i].mass = 1.0;
	pv[i].xold	  = particles[i].x;
	pv[i].yold	  = particles[i].y;
	pv[i].zold	  = particles[i].z;
	pv[i].fx	  = 0;
	pv[i].fy	  = 0;
	pv[i].fz	  = 0;
    }
}

double ComputeForces( Particle myparticles[], Particle others[], ParticleV pv[], int npart )
{
  double max_f;
  int i;
  max_f = 0.0;
  for (i=0; i<npart; i++) {
    int j;
    double xi, yi, mi, rx, ry, mj, r, fx, fy, rmin;
    rmin = 100.0;
    xi   = myparticles[i].x;
    yi   = myparticles[i].y;
    fx   = 0.0;
    fy   = 0.0;
    for (j=0; j<npart; j++) {
      rx = xi - others[j].x;
      ry = yi - others[j].y;
      mj = others[j].mass;
      r  = rx * rx + ry * ry;
      /* ignore overlap and same particle */
      if (r == 0.0) continue;
      if (r < rmin) rmin = r;
      r  = r * sqrt(r);
      fx -= mj * rx / r;
      fy -= mj * ry / r;
    }
    pv[i].fx += fx;
    pv[i].fy += fy;
    fx = sqrt(fx*fx + fy*fy)/rmin;
    if (fx > max_f) max_f = fx;
  }
  return max_f;
}

double ComputeNewPos( Particle particles[], ParticleV pv[], int npart, double max_f)
{
  int i;
  double a0, a1, a2;
  static double dt_old = 0.001, dt = 0.001;
  double dt_new;
  a0	 = 2.0 / (dt * (dt + dt_old));
  a2	 = 2.0 / (dt_old * (dt + dt_old));
  a1	 = -(a0 + a2);
  for (i=0; i<npart; i++) {
    double xi, yi;
    xi	           = particles[i].x;
    yi	           = particles[i].y;
    particles[i].x = (pv[i].fx - a1 * xi - a2 * pv[i].xold) / a0;
    particles[i].y = (pv[i].fy - a1 * yi - a2 * pv[i].yold) / a0;
    pv[i].xold     = xi;
    pv[i].yold     = yi;
    pv[i].fx       = 0;
    pv[i].fy       = 0;
  }
  dt_new = 1.0/sqrt(max_f);
  /* Set a minimum: */
  if (dt_new < 1.0e-6) dt_new = 1.0e-6;
  /* Modify time step */
  if (dt_new < dt) {
    dt_old = dt;
    dt     = dt_new;
  }
  else if (dt_new > 4.0 * dt) {
    dt_old = dt;
    dt    *= 2.0;
  }
  return dt_old;
}

