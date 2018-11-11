#include <iostream>
#include <iomanip>

using namespace std;

int LENGTH;

class Gene {
   public:
      int strand;
      int start;
      int end;
};

int generateComplementary(string* dna) {
  char temp[LENGTH];
  for (int i = 0; dna[0][i]; i++) {
    if (dna[0][i] != 'a' && dna[0][i] != 't' && dna[0][i] != 'c' && dna[0][i] != 'g' &&
          dna[0][i] != 'A' && dna[0][i] != 'T' && dna[0][i] != 'C' && dna[0][i] != 'G') {
      cout << "    ";
      cout << "\033[1;31mDNA ERROR\033[0m\n";
      return 1;
    }
    dna[0][i] = toupper(dna[0][i]);
    switch (dna[0][i]) {
      case 'A':
        temp[LENGTH - 1 - i] = 'T';
        break;
      case 'T':
        temp[LENGTH - 1 - i] = 'A';
        break;
      case 'C':
        temp[LENGTH - 1 - i] = 'G';
        break;
      case 'G':
        temp[LENGTH - 1 - i] = 'C';
        break;
    }
  }
  dna[1] = string(temp);
  return 0;
}

void printComplementary(string* dna) {
  cout << "DNA COMPLEMENTARY:\n";

  cout << "    ";
  cout << "INDEX:      |";
  for (int i = 0; i < 50; i++) {
    if ((i % 10) == 0) {
      cout << (i / 10);
    } else {
      cout << " ";
    }
  }
  cout << "|\n";
  cout << "                |";
  int index = 0;
  for (int i = 0; i < 50; i++) {
    if ((i % 10) == 0) {
      index = 0;
    }
    cout << index;
    index++;
  }
  cout << "|\n";

  int line = 1;
  cout << "    ";
  cout << "STRAND A: ";
  cout << "5' ";
  for (int i = 0; i < LENGTH; i++) {
    cout << dna[0][i];
    if ((line % 50) == 0) {
      cout << "\n";
      cout << "    ";
      cout << "    ";
      cout << "    ";
      cout << "    ";
      cout << " ";
    }
    line++;
  }
  for (int i = 0; i <= (50 - (line % 50)); i++) {
    cout << " ";
  }
  cout << " 3'\n";

  line = 1;
  cout << "    ";
  cout << "STRAND B: ";
  cout << "3' ";
  for (int i = (LENGTH - 1); i >= 0; i--) {
      cout << dna[1][i];
      if ((line % 50) == 0) {
        cout << "\n";
        cout << "    ";
        cout << "    ";
        cout << "    ";
        cout << "    ";
        cout << " ";
      }
      line++;
  }
  for (int i = 0; i <= (50 - (line % 50)); i++) {
    cout << " ";
  }
  cout << " 5'\n";
}

void printLength() {
  cout << "DNA LENGTH:\n";
  cout << "    ";
  cout << LENGTH << "\n";
}

void printGene(Gene gene, string* dna) {
  cout << "    ";
  cout << "STRAND ";
  int line = 1;
  if (gene.strand == 0) {
    cout << "A\n";
    cout << "    ";
    cout << "    ";
    cout << "INDEX [" << gene.start << "] - [" << gene.end << "]\n";
    cout << "    ";
    cout << "    ";
    cout << "LENGTH: " << (gene.end - gene.start + 1) << "\n";
    cout << "    ";
    cout << "    ";
    cout << "5' ";
    for (int i = gene.start; i <= gene.end; i++) {
      cout << dna[0][i];
      if ((line % 50) == 0) {
        cout << "\n";
        cout << "    ";
        cout << "    ";
        cout << "   ";
      }
      line++;
    }
    for (int i = 0; i <= (50 - (line % 50)); i++) {
      cout << " ";
    }
    cout << " 3'\n";
  } else if (gene.strand == 1) {
    cout << "B\n";
    cout << "    ";
    cout << "    ";
    cout << "INDEX [" << (LENGTH - 1 - gene.end) << "] - [" << (LENGTH - 1 - gene.start) << "]\n";
    cout << "    ";
    cout << "    ";
    cout << "LENGTH: " << (gene.end - gene.start + 1) << "\n";
    cout << "    ";
    cout << "    ";
    cout << "3' ";
    for (int i = gene.end; i >= gene.start; i--) {
      cout << dna[1][i];
      if ((line % 50) == 0) {
        cout << "\n";
        cout << "    ";
        cout << "    ";
        cout << "   ";
      }
      line++;
    }
    for (int i = 0; i <= (50 - (line % 50)); i++) {
      cout << " ";
    }
    cout << " 5'\n";
  }
}

Gene findLongestGene(string* dna) {
  bool found = false;
  int strand = 0;
  int start = 0;
  int end = 0;
  cout << "GENE/OPEN READING FRAME:\n";
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < (LENGTH - 2); j++) {
      if (dna[i][j] == 'A') {
        if (dna[i][j + 1] == 'T') {
          if (dna[i][j + 2] == 'G') { 
            for (int k = (j + 3); k < (LENGTH - 2); k = k + 3) {
              if (dna[i][k] == 'T') {
                if (dna[i][k + 1] == 'A') {
                  if (dna[i][k + 2] == 'A' || dna[i][k + 2] == 'G') {
                    found = true;
                    Gene gene;
                    gene.strand = i;
                    gene.start = j;
                    gene.end = (k + 2);
                    printGene(gene, dna);
                    if ((k - j) > (end - start)) {
                      strand = i;
                      start = j;
                      end = (k + 2);
                    }
                    break;
                  }
                } else if (dna[i][k + 1] == 'G') {
                  if (dna[i][k + 2] == 'A') {
                    found = true;
                    Gene gene;
                    gene.strand = i;
                    gene.start = j;
                    gene.end = (k + 2);
                    printGene(gene, dna);
                    if ((k - j) > (end - start)) {
                      strand = i;
                      start = j;
                      end = (k + 2);
                    }
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (!found) {
    cout << "    ";
    cout << "\033[1;31mNOT FOUND\033[0m\n";
    exit(0);
  }
  Gene longestGene;
  longestGene.strand = strand;
  longestGene.start = start;
  longestGene.end = end;
  return longestGene;
}

void printLongestGene(Gene longestGene, string* dna) {
  cout << '\n';
  cout << "THE LONGEST GENE/OPEN READING FRAME:\n";
  cout << "    ";
  cout << "STRAND ";
  int line = 1;
  if (longestGene.strand == 0) {
    cout << "A\n";
    cout << "    ";
    cout << "    ";
    cout << "INDEX: [" << longestGene.start << "] - [" << longestGene.end << "]\n";
    cout << "    ";
    cout << "    ";
    cout << "LENGTH: " << (longestGene.end - longestGene.start + 1) << "\n";
    cout << "    ";
    cout << "    ";
    cout << "5' ";
    for (int i = longestGene.start; i <= longestGene.end; i++) {
      cout << dna[0][i];
      if ((line % 50) == 0) {
        cout << "\n";
        cout << "    ";
        cout << "    ";
        cout << "   ";
      }
      line++;
    }
    for (int i = 0; i <= (50 - (line % 50)); i++) {
      cout << " ";
    }
    cout << " 3'\n";
  } else if (longestGene.strand == 1) {
    cout << "B\n";
    cout << "    ";
    cout << "    ";
    cout << "INDEX: [" << (LENGTH - 1 - longestGene.end) << "] - [" << (LENGTH - 1 - longestGene.start) << "]\n";
    cout << "    ";
    cout << "    ";
    cout << "LENGTH: " << (longestGene.end - longestGene.start + 1) << "\n";
    cout << "    ";
    cout << "    ";
    cout << "3' ";
    for (int i = longestGene.end; i >= longestGene.start; i--) {
      cout << dna[1][i];
      if ((line % 50) == 0) {
        cout << "\n";
        cout << "    ";
        cout << "    ";
        cout << "   ";
      }
      line++;
    }
    for (int i = 0; i <= (50 - (line % 50)); i++) {
      cout << " ";
    }
    cout << " 5'\n";
  }
}

string transcribe(Gene longestGene, string* dna) {
  int size = (longestGene.end - longestGene.start + 1);
  string mrna = dna[longestGene.strand].substr(longestGene.start, size);
  for (int i = 0; i < mrna.size(); i++) {
    if (mrna[i] == 'T') {
      mrna[i] = 'U';
    }
  }
  return mrna;
}

void printTranscription(string mrna) {
  cout << "TRANSCRIPTION\n";
  cout << "    ";
  cout << "mRNA:";
  cout << "\n";
  cout << "    ";
  cout << "    ";
  cout << "5' ";
  int line = 1;
  for (int i = 0; i < (int)mrna.size(); i++) {
    cout << mrna[i];
    if ((line % 50) == 0) {
      cout << "\n";
      cout << "    ";
      cout << "    ";
      cout << "   ";
    }
    line++;
  }
  for (int i = 0; i <= (50 - (line % 50)); i++) {
    cout << " ";
  }
  cout << " 3'";
  cout << '\n';
}

string translate(string mrna) {
  int count = 0;
  char aminoAcids[(mrna.size() / 3)];
  for (int i = 0; i < ((int)mrna.size() - 2); i = i + 3) {
    switch (mrna[i]) {
      case 'U':
        if (mrna[i + 1] == 'U') {
          if (mrna[i + 2] == 'U' || mrna[i + 2] == 'C') {
            // Phe
            aminoAcids[count] = 'F';
          } else if (mrna[i + 2] == 'A' || mrna[i + 2] == 'G') {
            // Leu
            aminoAcids[count] = 'L';
          }
        } else if (mrna[i + 1] == 'C') {
          // Ser
          aminoAcids[count] = 'S';
        } else if (mrna[i + 1] == 'A') {
          if (mrna[i + 2] == 'U' || mrna[i + 2] == 'C') {
            // Tyr
            aminoAcids[count] = 'Y';
          } else if (mrna[i + 2] == 'A' || mrna[i + 2] == 'G') {
            // STOP
            aminoAcids[count] = 0;
          }
        } else if (mrna[i + 1] == 'G') {
          if (mrna[i + 2] == 'U' || mrna[i + 2] == 'C') {
            // Cys
            aminoAcids[count] = 'C';
          } else if (mrna[i + 2] == 'A') {
            // Stop
            aminoAcids[count] = 0;
          } else if (mrna[i + 2] == 'G') {
            // Trp
            aminoAcids[count] = 'W';
          }
        }
        break;
      case 'C':
        if (mrna[i + 1] == 'U') {
          // Leu
          aminoAcids[count] = 'L';
        } else if (mrna[i + 1] == 'C') {
          // Pro
          aminoAcids[count] = 'P';
        } else if (mrna[i + 1] == 'A') {
          if (mrna[i + 2] == 'U' || mrna[i + 2] == 'C') {
            // His
            aminoAcids[count] = 'H';
          } else if (mrna[i + 2] == 'A' || mrna[i + 2] == 'G') {
            // Gln
            aminoAcids[count] = 'Q';
          }
        } else if (mrna[i + 1] == 'G') {
          // Arg
          aminoAcids[count] = 'R';
        }
        break;
      case 'A':
        if (mrna[i + 1] == 'U') {
          if (mrna[i + 2] == 'U' || mrna[i + 2] == 'C' || mrna[i + 2] == 'A') {
            // Ile
            aminoAcids[count] = 'I';
          } else if (mrna[i + 2] == 'G') {
            // Met
            aminoAcids[count] = 'M';
          }
        } else if (mrna[i + 1] == 'C') {
          // Thr
          aminoAcids[count] = 'T';
        } else if (mrna[i + 1] == 'A') {
          if (mrna[i + 2] == 'U' || mrna[i + 2] == 'C') {
            // Asn
            aminoAcids[count] = 'N';
          } else if (mrna[i + 2] == 'A' || mrna[i + 2] == 'G') {
            // Lys
            aminoAcids[count] = 'K';
          }
        } else if (mrna[i + 1] == 'G') {
          if (mrna[i + 2] == 'U' || mrna[i + 2] == 'C') {
            // Ser
            aminoAcids[count] = 'S';
          } else if (mrna[i + 2] == 'A' || mrna[i + 2] == 'G') {
            // Arg
            aminoAcids[count] = 'R';
          }
        }
        break;
      case 'G':
        if (mrna[i + 1] == 'U') {
          // Val
          aminoAcids[count] = 'V';
        } else if (mrna[i + 1] == 'C') {
          // Ala
          aminoAcids[count] = 'A';
        } else if (mrna[i + 1] == 'A') {
          if (mrna[i + 2] == 'U' || mrna[i + 2] == 'C') {
            // Asp
            aminoAcids[count] = 'D';
          } else if (mrna[i + 2] == 'A' || mrna[i + 2] == 'G') {
            // Glu
            aminoAcids[count] = 'E';
          }
        } else if (mrna[i + 1] == 'G') {
          // Gly
          aminoAcids[count] = 'G';
        }
        break;
    }
    count++;
  }
  return string(aminoAcids);
}

void printTranslation(string aminoAcids) {
  cout << "TRANSLATION\n";
  cout << "    ";
  cout << "AMINO ACIDS:";
  cout << "\n";
  cout << "    ";
  cout << "    ";
  cout << "   ";
  int line = 1;
  for (int i = 0; i < (int)aminoAcids.size(); i++) {
    cout << aminoAcids[i];
    if ((line % 50) == 0) {
      cout << "\n";
      cout << "    ";
      cout << "    ";
      cout << "   ";
    }
    line++;
  }
  cout << '\n';
}

int main() {
  string dna[2];
  Gene longestGene;
  string mrna;
  string aminoAcids;

  cout << "Enter a DNA sequence (from 5’ to 3’): ";
  getline (cin, dna[0]);
  //dna[0] = "TCAATGTAACGCGCTACCCGGAGCTCTGGGCCCAAATTTCATCCACT";
  LENGTH = dna[0].size();
  if (generateComplementary(dna)) {
    return 1;
  }
  cout << "\n";

  printComplementary(dna);
  cout << '\n';

  printLength();
  cout << '\n';

  longestGene = findLongestGene(dna);
  printLongestGene(longestGene, dna);
  cout << '\n';

  mrna = transcribe(longestGene, dna);
  printTranscription(mrna);
  cout << "\n";

  aminoAcids = translate(mrna);
  printTranslation(aminoAcids);

  return 0;
}
