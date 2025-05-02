# 🚌 Simulation de Bus dans un Tunnel à Voie Unique

## Participants

- [Djelloul Faiza] 
- [Amzal Mayar]
- [Chirane Tarek Abdelaziz]

## 📘 Contexte

Deux villes, **X** et **Y**, sont reliées par un tunnel à **voie unique** emprunté quotidiennement par des **bus de transport en commun**.

Chaque bus réalise **10 trajets aller-retour** (soit 20 passages dans le tunnel).

---

## ⚙️ Règles de circulation

- 🚫 **Pas de croisement** : aucun bus ne peut entrer dans le tunnel si des bus arrivent en sens inverse.
- 👥 **Circulation groupée** : plusieurs bus dans le même sens peuvent traverser ensemble.
- ⚖️ **Équité** : un sens ne doit pas monopoliser le tunnel.
- 🔁 **Allers-retours** : chaque bus fait 10 allers-retours par jour.

---

## 🧠 Fonctionnement du programme

### 🔷 Version C

- ✅ Création de 9 bus (threads) :  
  5 depuis la ville X et 4 depuis la ville Y.  
  Chaque bus effectue 10 allers-retours (20 trajets).

- 🔁 Tunnel à sens unique :  
  Un seul sens de circulation autorisé à la fois.  
  Les bus attendent que le tunnel soit vide ou que leur sens corresponde au sens courant.

- 🚦 Synchronisation :
  - pthread_mutex_t pour les sections critiques.
  - sem_t pour gérer l’accès au tunnel et assurer l’équité.

- 🕒 Simulation de trajet :  
  Chaque trajet utilise un sleep() ou usleep() avec un délai aléatoire entre 1 et 1.5 secondes.

- 🧹 Nettoyage :  
  Tous les threads sont rejoints (pthread_join) et les sémaphores détruits (sem_destroy).

---

### 🐍 Version Python

- ✅ Création de 9 threads représentant les bus :  
  5 depuis X, 4 depuis Y, chacun effectuant 10 allers-retours.

- 🔁 Tunnel à sens unique :  
  Un seul sens de circulation à la fois, comme en C.

- 🚦 Synchronisation :
  - threading.Lock() pour protéger les ressources partagées.
  - threading.Semaphore() pour gérer le nombre de bus et l’équité.

- 🕒 Simulation de trajet :  
  Utilise time.sleep(random.uniform(1, 1.5)) pour simuler un trajet.

- 🧹 Nettoyage automatique :  
  Les threads sont rejoints (join) et aucune libération manuelle n’est nécessaire.

---

🎯 Conclusion :  
Les deux versions respectent les contraintes du problème :  
- pas de croisement dans le tunnel  
- trajets groupés dans un même sens  
- respect de l’équité entre les directions  
- utilisation correcte des sémaphores et mutex
  
---

## ▶️ Exécution

### 1. Prérequis
en Python:
- Python 3.x
en C:
-C/C++


### 2. Installation
en Python:
```bash
git clone https://github.com/faizaxlol/tunnel-bus-simulation.git
cd tunnel-bus-simulation
pip install -r requirements.txt

en C:
```bash
wsl
mkdir ~/projet
cd ~/projet
gcc -o tunnel tunnel_sync.c -lpthread
./tunnel

