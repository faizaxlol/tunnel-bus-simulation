import threading
import time
import random

# verrou pour protéger les variables partagées
mutex = threading.Lock()

# variables de comptage
bus_dans_tunnel = 0
sens_actuel = None  # soit "X->Y" soit "Y->X"
attente_XY = 0
attente_YX = 0

# sémaphore pour garantir équité
tunnel = threading.Semaphore(1)

def log(message):
    print(f"[{time.strftime('%H:%M:%S')}] {message}")

def trajet(bus_id, ville, depart, arrivee, i):
    log(f"Bus {bus_id} de {ville} : {depart} -> {arrivee} (Trajet {i})")
    time.sleep(random.uniform(1, 1.5))

def entrer_tunnel(direction):
    global bus_dans_tunnel, sens_actuel, attente_XY, attente_YX
    with mutex:
        if direction == "X->Y":
            attente_XY += 1
        else:
            attente_YX += 1

    while True:
        with mutex:
            if (bus_dans_tunnel == 0 or sens_actuel == direction):
                if direction == "X->Y":
                    attente_XY -= 1
                else:
                    attente_YX -= 1
                bus_dans_tunnel += 1
                sens_actuel = direction
                return
        time.sleep(0.1)

def sortir_tunnel():
    global bus_dans_tunnel, sens_actuel
    with mutex:
        bus_dans_tunnel -= 1
        if bus_dans_tunnel == 0:
            # on change de sens si des bus attendent dans l’autre direction
            if sens_actuel == "X->Y" and attente_YX > 0:
                sens_actuel = "Y->X"
            elif sens_actuel == "Y->X" and attente_XY > 0:
                sens_actuel = "X->Y"

def bus_thread(bus_id, ville):
    sens_depart = "X->Y" if ville == "X" else "Y->X"
    sens_retour = "Y->X" if ville == "X" else "X->Y"
    for i in range(1, 11):
        # trajet aller
        entrer_tunnel(sens_depart)
        trajet(bus_id, ville, sens_depart.split("->")[0], sens_depart.split("->")[1], i)
        sortir_tunnel()

        # trajet retour
        entrer_tunnel(sens_retour)
        trajet(bus_id, ville, sens_retour.split("->")[0], sens_retour.split("->")[1], i)
        sortir_tunnel()

def main():
    threads = []

    # ville X : 5 bus
    for i in range(1, 6):
        t = threading.Thread(target=bus_thread, args=(i, "X"))
        threads.append(t)

    # ville Y : 4 bus
    for i in range(6, 10):
        t = threading.Thread(target=bus_thread, args=(i, "Y"))
        threads.append(t)

    # démarrage
    for t in threads:
        t.start()

    # attendre la fin
    for t in threads:
        t.join()

    log("Tous les bus ont terminé leurs trajets.")

if __name__ == "__main__":
    main()
