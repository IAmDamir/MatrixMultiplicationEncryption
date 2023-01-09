// Assignment4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

std::vector<std::vector<float>> AssignMatrix(std::vector<std::vector<float>>& matrix);
std::vector<float> MultiplyMatrixAndVector(
	const std::vector<std::vector<float>>& matrix,
	const std::vector<float>& vec);
int AssignAlphabetToNumerical(const char& ch);
float findDeterminant(std::vector<std::vector<float>> matrix3X3);
void adjoint(std::vector<std::vector<float>> matrix3X3);
std::vector<std::vector<float>> inverse(std::vector<std::vector<float>> matrix3X3, float d);

int main()
{
	std::vector<std::vector<float>> matrix;
	std::vector<std::vector<float>> inverseMatrix;
	std::vector<float> originalText;
	std::vector<float> encryptedText;
	std::vector<float> decryptedText;
	std::string key;

	AssignMatrix(matrix);

	do {
		std::cout << "Please use a word with x3 number of characters\n";
		std::cin >> key;
	} while (key.size() % 3 != 0);

	for (const char& ch : key)
		originalText.push_back(AssignAlphabetToNumerical(ch));

	for (const auto& n : originalText)
		std::cout << n << ' ';
	std::cout << std::endl;

	encryptedText = MultiplyMatrixAndVector(matrix, originalText);

	std::cout << "\nencryptedText is: ";
	for (const auto& ch : encryptedText)
		std::cout << ch << ' ';
	std::cout << std::endl;

	// Finding inverse of the matrix
	float determinant = findDeterminant(matrix);
	std::cout << "\n\nDeteterminant of the given matrix is : " << determinant;
	if (determinant != 0) {
		adjoint(matrix);
		inverseMatrix = inverse(matrix, determinant);
	}
	else
	{
		std::cout << " As the determinant of the given matrix is 0, so we cannot take find it's Inverse :";
		return 0;
	}

	decryptedText = MultiplyMatrixAndVector(inverseMatrix, encryptedText);
	std::cout << "\ndecryptedText is: ";
	for (const auto& ch : decryptedText)
		std::cout << ch << ' ';
	std::cout << std::endl;

	for (const auto& ch : decryptedText)
		std::cout << (char)ceil(ch + 'a' - 1) << ' ';
}

std::vector<std::vector<float>> AssignMatrix(std::vector<std::vector<float>>& matrix)
{
	std::cout << "Would you like to make random matrix?\n";
	std::string answer;
	std::cin >> answer;
	for (char& ch : answer)
		ch = tolower(ch);

	if (answer == "yes" || answer == "y")
	{
		/* initialize random seed: */
		srand(time(NULL));

		for (int i = 0; i < 3; i++)
		{
			std::vector<float> tempVec;
			for (int j = 0; j < 3; j++)
			{
				tempVec.push_back(rand() % 10 + 1);
			}
			matrix.push_back(tempVec);
		}
	}
	else
	{
		std::cout << "Please write 3x3 Matrix\n";
		for (int i = 0; i < 3; i++)
		{
			std::vector<float> tempVec;
			for (int j = 0; j < 3; j++)
			{
				int tempInt = 0;
				std::cin >> tempInt;
				tempVec.push_back(tempInt);
			}
			matrix.push_back(tempVec);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		std::vector<int> tempVec;
		for (int j = 0; j < 3; j++)
		{
			std::cout << matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	return matrix;
}

int AssignAlphabetToNumerical(const char& ch)
{
	return tolower(ch) - 'a' + 1;
}

float findDeterminant(std::vector<std::vector<float>> matrix3X3)
{
	float det = 0; // here det is the determinant of the matrix.
	for (int r = 0; r < 3; r++) {
		det = det + (matrix3X3[0][r] * (matrix3X3[1][(r + 1) % 3] * matrix3X3[2][(r + 2) % 3]
			- matrix3X3[1][(r + 2) % 3] * matrix3X3[2][(r + 1) % 3]));
	}
	return det;
}

void adjoint(std::vector<std::vector<float>>  matrix3X3)
{
	std::cout << "\n\nAdjoint of matrix is: \n";
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			std::cout << ((matrix3X3[(c + 1) % 3][(r + 1) % 3] * matrix3X3[(c + 2) % 3][(r + 2) % 3])
				- (matrix3X3[(c + 1) % 3][(r + 2) % 3] * matrix3X3[(c + 2) % 3][(r + 1) % 3]))
				<< "\t";
		}
		std::cout << std::endl;
	}
}

std::vector<std::vector<float>> inverse(std::vector<std::vector<float>> matrix3X3, float d)
{
	std::vector<std::vector<float>> result;

	std::cout << "\n\nInverse of matrix is: \n";
	for (int r = 0; r < 3; r++)
	{
		std::vector<float> tempVec;
		for (int c = 0; c < 3; c++)
		{
			float temp = ((matrix3X3[(c + 1) % 3][(r + 1) % 3] * matrix3X3[(c + 2) % 3][(r + 2) % 3])
				- (matrix3X3[(c + 1) % 3][(r + 2) % 3] * matrix3X3[(c + 2) % 3][(r + 1) % 3])) / d;
			std::cout << temp << "\t";
			tempVec.push_back(temp);
		}
		result.push_back(tempVec);
		std::cout << std::endl;
	}

	return result;
}

std::vector<float> MultiplyMatrixAndVector(
	const std::vector<std::vector<float>>& matrix,
	const std::vector<float>& vec)
{
	std::vector<float> result;

	int v = 0;
	for (int i = 0, j = 0; j < vec.size(); ++i, ++j)
	{
		if (i == 3)
		{
			i = 0;
			v++;
		}

		int temp = 0;
		for (int k = 0, l = v * 3; k < 3; ++k, ++l)
		{
			temp += matrix[i][k] * vec[l];
		}
		result.push_back(temp);
	}

	return result;
}