#define _USE_MATH_DEFINES // always before the include

#include <math.h>
#include <vector>
#include <string.h>

#include "primitives.h"
#include "../utils/ponto.h"

using namespace std;


// Cria��o de um plano na superf�cie do plano XZ.
vector<Ponto> plane(float size) {

	//vector<Ponto> � o mesmo que ter um array dinamico de Ponto
	vector<Ponto> pontos;

	float distancia = size / 2;

	pontos.push_back(Ponto(distancia, 0, distancia));
	pontos.push_back(Ponto(distancia, 0, -distancia));
	pontos.push_back(Ponto(-distancia, 0, -distancia));

	pontos.push_back(Ponto(-distancia, 0, -distancia));
	pontos.push_back(Ponto(-distancia, 0, distancia));
	pontos.push_back(Ponto(distancia, 0, distancia));

	return pontos;

}

vector<Ponto> criaCubo(float iniX, float iniY, float iniZ, float dimX, float dimY, float dimZ, int divX, int divY, int divZ) {

	vector<Ponto> pontos;

	//CONTRUINDO POR FACES TEMOS:

	// Plano xz pos
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY, -iniZ + divZ * dimZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY, -iniZ + divZ * dimZ));

	pontos.push_back(Ponto(-iniX + divX * dimX, iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY, -iniZ + divZ * dimZ));

	// Plano xz neg
	pontos.push_back(Ponto(-iniX + divX * dimX, -iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, -iniY, -iniZ + divZ * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, -iniY, -iniZ + divZ * dimZ));

	pontos.push_back(Ponto(-iniX + divX * dimX, -iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, -iniY, -iniZ + divZ * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, -iniY, -iniZ + (divZ + 1) * dimZ));

	// Plano xy pos
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - divY * dimY, iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - divY * dimY, iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - (divY + 1) * dimY, iniZ));

	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - (divY + 1) * dimY, iniZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - divY * dimY, iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - (divY + 1) * dimY, iniZ));

	// Plano xy neg
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - divY * dimY, -iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - (divY + 1) * dimY, -iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - divY * dimY, -iniZ));

	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - (divY + 1) * dimY, -iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - (divY + 1) * dimY, -iniZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - divY * dimY, -iniZ));


	// Plano yz pos
	pontos.push_back(Ponto(iniX, iniY - (divY + 1) * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(iniX, iniY - (divY + 1) * dimY, iniZ - (divZ + 1) * dimZ));
	pontos.push_back(Ponto(iniX, iniY - divY * dimY, iniZ - (divZ + 1) * dimZ));

	pontos.push_back(Ponto(iniX, iniY - (divY + 1) * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(iniX, iniY - divY * dimY, iniZ - (divZ + 1) * dimZ));
	pontos.push_back(Ponto(iniX, iniY - divY * dimY, iniZ - divZ * dimZ));

	// Plano yz neg
	pontos.push_back(Ponto(-iniX, iniY - (divY + 1) * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(-iniX, iniY - divY * dimY, iniZ - (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX, iniY - (divY + 1) * dimY, iniZ - (divZ + 1) * dimZ));

	pontos.push_back(Ponto(-iniX, iniY - (divY + 1) * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(-iniX, iniY - divY * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(-iniX, iniY - divY * dimY, iniZ - (divZ + 1) * dimZ));


	return pontos;
}

// Cria��o de uma box com as dimens�es dadas e com um numero de Divis�es em iguais sec��es da caixa
vector<Ponto> box(float dimX, float dimY, float dimZ, int nrDivisoes) {

	vector<Ponto> pontos;

	float inicialX = dimX / 2;
	float inicialY = dimY / 2;
	float inicialZ = dimZ / 2;

	float distanicaX = dimX / nrDivisoes;
	float distanicaY = dimY / nrDivisoes;
	float distanicaZ = dimZ / nrDivisoes;

	// Se tivermos 2 divis�es, pasamos a ter 8 cubos.
	// Temos de fazer ent�o 3 for (um para a divis�o em cada eixo)
	for (int divX = 0; divX < nrDivisoes; divX++) {
		for (int divY = 0; divY < nrDivisoes; divY++) {
			for (int divZ = 0; divZ < nrDivisoes; divZ++) {

				//Cria um vector de Pontos para todos os cubos que v�o fazer parte da Box
				vector<Ponto> novosPontos = criaCubo(inicialX, inicialY, inicialZ, distanicaX, distanicaY, distanicaZ, divX, divY, divZ);

				//Junta os pontos de um cubinho aos pontos que j� tinha de cubos anteriores que formavam a caixa
				pontos.insert(pontos.end(), novosPontos.begin(), novosPontos.end());

			}
		}
	}

	return pontos;
}

//Cria��o de um cone com um dado raio, uma altura, nr slices e de stacks
vector<Ponto> cone(float raioBase, float alturaCone, int nrSlices, int nrStacks) {

	vector<Ponto> pontos;

	float defaultAngleFatia = (2 * M_PI) / nrSlices;
	float alturaStack = alturaCone / nrStacks;
	float mudancaRaioStack = raioBase / nrStacks;

	for (int fatiaNr = 0; fatiaNr < nrSlices; fatiaNr++) {

		float angulo = fatiaNr * defaultAngleFatia;
		float proxAngulo = angulo + defaultAngleFatia;

		float alturaAtual = 0;
		float proxAltura = alturaStack;

		float raioAtual = raioBase;
		float proxRaio = raioBase - mudancaRaioStack;


		// Base
		pontos.push_back(Ponto(0.0f, 0.0f, 0.0f));
		pontos.push_back(Ponto(raioBase * cos(angulo), 0.0f, raioBase * sin(angulo)));
		pontos.push_back(Ponto(raioBase * cos(proxAngulo), 0.0f, raioBase * sin(proxAngulo)));

		for (int nrCamada = 1; nrCamada < nrStacks; nrCamada++) {

			//Triangulo de stacks intermédias que compõe um quadrado
			pontos.push_back(Ponto(proxRaio * cos(proxAngulo), proxAltura, proxRaio * sin(proxAngulo)));
			pontos.push_back(Ponto(raioAtual * cos(proxAngulo), alturaAtual, raioAtual * sin(proxAngulo)));
			pontos.push_back(Ponto(raioAtual * cos(angulo), alturaAtual, raioAtual * sin(angulo)));

			//Triangulo de stacks intermédias que compõe um quadrado
			pontos.push_back(Ponto(proxRaio * cos(angulo), proxAltura, proxRaio * sin(angulo)));
			pontos.push_back(Ponto(proxRaio * cos(proxAngulo), proxAltura, proxRaio * sin(proxAngulo)));
			pontos.push_back(Ponto(raioAtual * cos(angulo), alturaAtual, raioAtual * sin(angulo)));

			alturaAtual += alturaStack;
			proxAltura += alturaStack;

			raioAtual -= mudancaRaioStack;
			proxRaio -= mudancaRaioStack;
		}

		//Triângulos ultima stack
		pontos.push_back(Ponto(raioAtual * cos(proxAngulo), alturaAtual, raioAtual * sin(proxAngulo)));
		pontos.push_back(Ponto(raioAtual * cos(angulo), alturaAtual, raioAtual * sin(angulo)));
		pontos.push_back(Ponto(0.0f, alturaCone, 0.0f));

	}

	return pontos;
}

//Cria��o de uma esfera com um dado raio, nr slices e de stacks
vector<Ponto> sphere(float raio, int nrSlices, int nrStacks) {

	vector<Ponto> pontos;

	float defaultAngleFatia = (2 * M_PI) / nrSlices;
	float defaultAngleStack = M_PI / nrStacks;

	for (int fatiaNr = 0; fatiaNr < nrSlices; fatiaNr++) {

		float anguloFatia = fatiaNr * defaultAngleFatia;
		float proxAnguloFatia = anguloFatia + defaultAngleFatia;

		float anguloStack = - M_PI_2;
		float proxAnguloStack = anguloStack + defaultAngleStack;

		// Para perceber ver slides P03, mais especificamente página 3/9 (tem lá as fórmulas e a explicação)

		//Podemos tentar arranjar e colocar tudo dentro do mesmo for com if's da primeira e ultima posição

		//Triângulos da primeira stack
		pontos.push_back(Ponto(0.0f, -raio, 0.0f));
		pontos.push_back(Ponto(raio * cos(proxAnguloStack) * sin(anguloFatia), raio * sin (proxAnguloStack) , raio * cos(proxAnguloStack) * cos(anguloFatia)));
		pontos.push_back(Ponto(raio * cos(proxAnguloStack) * sin(proxAnguloFatia), raio * sin(proxAnguloStack), raio * cos(proxAnguloStack) * cos(proxAnguloFatia)));

		anguloStack += defaultAngleStack;
		proxAnguloStack += defaultAngleStack;

		for (int nrCamada = 1; nrCamada < nrStacks; nrCamada++) {

			//Trinagulo de stacks intermédias que compõe um quadrado
			pontos.push_back(Ponto(raio * cos(anguloStack) * sin(anguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(anguloFatia)));
			pontos.push_back(Ponto(raio * cos(anguloStack) * sin(proxAnguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(proxAnguloFatia)));
			pontos.push_back(Ponto(raio * cos(proxAnguloStack) * sin(anguloFatia), raio * sin(proxAnguloStack), raio * cos(proxAnguloStack) * cos(anguloFatia)));

			//Trinagulo de stacks intermédias que compõe um quadrado
			pontos.push_back(Ponto(raio * cos(anguloStack) * sin(proxAnguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(proxAnguloFatia)));
			pontos.push_back(Ponto(raio * cos(proxAnguloStack) * sin(proxAnguloFatia), raio * sin(proxAnguloStack), raio * cos(proxAnguloStack) * cos(proxAnguloFatia)));
			pontos.push_back(Ponto(raio * cos(proxAnguloStack) * sin(anguloFatia), raio * sin(proxAnguloStack), raio * cos(proxAnguloStack) * cos(anguloFatia)));

			anguloStack += defaultAngleStack;
			proxAnguloStack += defaultAngleStack;
		}

		//Triângulos da ultima stack
		pontos.push_back(Ponto(0.0f, raio, 0.0f));
		pontos.push_back(Ponto(raio * cos(anguloStack) * sin(proxAnguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(proxAnguloFatia)));
		pontos.push_back(Ponto(raio * cos(anguloStack) * sin(anguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(anguloFatia)));
		
		anguloStack += defaultAngleStack;
		proxAnguloStack += defaultAngleStack;
	}

	return pontos;
}
