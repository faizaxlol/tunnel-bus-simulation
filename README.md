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

- Chaque bus est modélisé par un **thread Python**.
- Un **mutex** protège les variables partagées.
- Des **sémaphores** assurent l'exclusion mutuelle et l’équité.
- Les trajets sont simulés avec `sleep` aléatoire entre `1` et `1.5` secondes.

---

## ▶️ Exécution

### 1. Prérequis

- Python 3.x

### 2. Installation

```bash
git clone https://github.com/faizaxlol/tunnel-bus-simulation.git
cd tunnel-bus-simulation
pip install -r requirements.txt
