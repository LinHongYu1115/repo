#include <iostream>
#include <cmath> // for pow function
#include <chrono> // for performance measurement
using namespace std;
using namespace std::chrono;

class Polynomial; // forward declaration

class Term {
public:
    float coef; // coefficient
    int exp;    // exponent
};

class Polynomial {
    // p(x) = ax + + anx"; a set of ordered pairs of <e¡, a₁>,
    // where a; is a nonzero float coefficient and e; is a non-negative integer exponent.
public:
    Polynomial();
    Polynomial(const Term* terms, int termCount);
    // Construct the polynomial p (x) = 0.

    Polynomial Add(Polynomial poly);
    // Return the sum of the polynomials *this and poly.

    Polynomial Mult(Polynomial poly);
    // Return the product of the polynomials *this and poly.

    float Eval(float f);
    // Evaluate the polynomial *this at f and return the result.

    friend ostream& operator<<(ostream& os, const Polynomial& p);
    friend istream& operator>>(istream& is, Polynomial& p);

private:
    Term* termArray; // array of nonzero terms
    int capacity;    // size of termArray
    int terms;       // number of nonzero terms
};

Polynomial::Polynomial() : termArray(nullptr), capacity(0), terms(0) {}

Polynomial::Polynomial(const Term* terms, int termCount) {
    this->terms = termCount;
    this->capacity = this->terms;
    this->termArray = new Term[this->capacity];
    for (int i = 0; i < this->terms; ++i) {
        this->termArray[i] = terms[i];
    }
}

istream& operator>>(istream& is, Polynomial& p) {
    cout << "Enter number of terms: ";
    is >> p.terms;
    p.capacity = p.terms;
    p.termArray = new Term[p.capacity];
    for (int i = 0; i < p.terms; ++i) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        is >> p.termArray[i].coef >> p.termArray[i].exp;
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& p) {
    for (int i = 0; i < p.terms; ++i) {
        os << p.termArray[i].coef << "x^" << p.termArray[i].exp;
        if (i < p.terms - 1) os << " + ";
    }
    return os;
}

Polynomial Polynomial::Add(Polynomial poly) {
    int maxTerms = terms + poly.terms;
    Term* resultTerms = new Term[maxTerms];
    int i = 0, j = 0, k = 0;

    while (i < terms && j < poly.terms) {
        if (termArray[i].exp == poly.termArray[j].exp) {
            resultTerms[k].coef = termArray[i].coef + poly.termArray[j].coef;
            resultTerms[k].exp = termArray[i].exp;
            i++; j++;
        } else if (termArray[i].exp > poly.termArray[j].exp) {
            resultTerms[k] = termArray[i];
            i++;
        } else {
            resultTerms[k] = poly.termArray[j];
            j++;
        }
        k++;
    }

    while (i < terms) {
        resultTerms[k++] = termArray[i++];
    }

    while (j < poly.terms) {
        resultTerms[k++] = poly.termArray[j++];
    }

    // 合併相同指數的項
    for (int m = 0; m < k - 1; ++m) {
        for (int n = m + 1; n < k; ++n) {
            if (resultTerms[m].exp == resultTerms[n].exp) {
                resultTerms[m].coef += resultTerms[n].coef;
                for (int p = n; p < k - 1; ++p) {
                    resultTerms[p] = resultTerms[p + 1];
                }
                k--;
                n--;
            }
        }
    }

    Polynomial result(resultTerms, k);
    delete[] resultTerms;
    return result;
}

Polynomial Polynomial::Mult(Polynomial poly) {
    int maxTerms = terms * poly.terms;
    Term* resultTerms = new Term[maxTerms];
    int k = 0;

    for (int i = 0; i < terms; ++i) {
        for (int j = 0; j < poly.terms; ++j) {
            resultTerms[k].coef = termArray[i].coef * poly.termArray[j].coef;
            resultTerms[k].exp = termArray[i].exp + poly.termArray[j].exp;
            k++;
        }
    }

    // 合併相同指數的項
    for (int m = 0; m < k - 1; ++m) {
        for (int n = m + 1; n < k; ++n) {
            if (resultTerms[m].exp == resultTerms[n].exp) {
                resultTerms[m].coef += resultTerms[n].coef;
                for (int p = n; p < k - 1; ++p) {
                    resultTerms[p] = resultTerms[p + 1];
                }
                k--;
                n--;
            }
        }
    }

    Polynomial result(resultTerms, k);
    delete[] resultTerms;
    return result;
}

float Polynomial::Eval(float f) {
    float result = 0.0;
    for (int i = 0; i < terms; ++i) {
        result += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return result;
}

int main() {
    Polynomial poly1, poly2;
    cout << "Enter number of terms and then coefficient and exponent for each term for the first polynomial:" << endl;
    cin >> poly1;
    cout << "Enter number of terms and then coefficient and exponent for each term for the second polynomial:" << endl;
    cin >> poly2;

    auto start = high_resolution_clock::now();
    Polynomial sum = poly1.Add(poly2);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken for addition: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    Polynomial product = poly1.Mult(poly2);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Time taken for multiplication: " << duration.count() << " microseconds" << endl;

    cout << "First polynomial: ";
    cout << poly1 << endl;
    cout << "Second polynomial: ";
    cout << poly2 << endl;
    cout << "Sum: ";
    cout << sum << endl;
    cout << "Product: ";
    cout << product << endl;

    float evalPoint;
    cout << "Enter a value to evaluate the polynomials: ";
    cin >> evalPoint;

    cout << "First polynomial evaluated at " << evalPoint << ": " << poly1.Eval(evalPoint) << endl;
    cout << "Second polynomial evaluated at " << evalPoint << ": " << poly2.Eval(evalPoint) << endl;
    cout << "Sum evaluated at " << evalPoint << ": " << sum.Eval(evalPoint) << endl;
    cout << "Product evaluated at " << evalPoint << ": " << product.Eval(evalPoint) << endl;

    return 0;
}
