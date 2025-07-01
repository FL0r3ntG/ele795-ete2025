# Gant haptique VR – Projet de fin d'études ÉTS

![LucidGloves](https://cdn.discordapp.com/attachments/785135646082990120/873666310855360582/LucidGlovesBlackwbkgnd.png)

Ce projet est une amélioration du micrologiciel open-source des **LucidGloves**, réalisé dans le cadre d'un **projet de fin d'études (PFE)** à l'**École de technologie supérieure (ÉTS)**, à Montréal.

---

## 🎓 Contexte académique

Ce projet est effectué dans le cadre du cours **ELE795 – Projet de fin d'études** en génie. Il est encadré par deux professeurs de l'ÉTS et réalisé en collaboration avec le club étudiant **Conjure**, spécialisé en réalité virtuelle et médias interactifs.

**Nom de l'équipe** : Gantastique  
**Date du projet** : Été 2025  
**Club client** : Conjure (ÉTS)  
**Projet client** : Carnaval VR

### Membres de l'équipe Gantastique

- **Myiah Catwell** – Génie électrique  
- **Florent Gilbert** – Génie électrique  
- **Julie Maurice** – Génie électrique  
- **Camylle Lupien** – Génie logiciel

### Superviseurs

- Claude Thibeault  
- David Labbé

---

## 🧤 Objectif du projet

Développer un **gant haptique immersif** destiné à des démonstrations éducatives de réalité virtuelle. Ce gant doit :

- Fournir des **retours sensoriels réalistes** (force, vibration, chaleur),
- Être **compact**, **sans fil** et **facile à enfiler**,
- S'intégrer facilement à un environnement **Unity** (Carnaval VR),
- Reposer sur une architecture **modulaire** avec un circuit imprimé (PCB),
- Respecter un **budget étudiant** limité à 500 $.

---

## ⚙️ Description technique

Le système est basé sur les LucidGloves avec plusieurs améliorations matérielles et logicielles :

### Architecture électronique

- **Microcontrôleur** : ESP32 (Bluetooth/Wi-Fi intégré)
- **Capteurs** : Potentiomètres flexibles pour capter la position des doigts
- **Actionneurs** :
  - Servomoteurs pour le retour de force (index, pouce)
  - Modules Peltier pour les variations de température
  - Vibreurs tactiles pour retours haptiques rapides
- **Circuit imprimé (PCB)** : compact, adapté à la forme du gant
- **Alimentation** : Batterie LiPo, autonomie d'environ 1 heure
- **Suivi de main** : Solution alternative aux manettes Vive/Quest 2 (ex. capteurs inertiels)

### Plateformes logicielles

- **Firmware** : Adaptation du micrologiciel LucidGloves pour ESP32
- **IDE** : Visual Studio Code avec PlatformIO
- **Environnement VR** : Unity 3D
- **Intégration VR** : SteamVR / OpenVR via OpenGloves
- **Communication** : Sérialisation de données via Bluetooth/Wi-Fi

---

## ✅ Objectifs techniques

1. **Retour de force** : Doigts contraints mécaniquement avec des servos synchronisés aux événements VR.
2. **Retour thermique** : Modules chauffants pour simuler des variations de température (25°C à 35°C).
3. **Vibration tactile** : Vibreurs au niveau du pouce et de l'index.
4. **Architecture compacte** : Intégration d'un PCB dans le gant avec gestion des câbles.
5. **Ergonomie** : Enfilage < 10 secondes, gant léger et confortable.
6. **Compatibilité logicielle** : Intégration facile avec Unity + documentation API.
7. **Sans fil** : Transmission Bluetooth (ou Wi-Fi) stable.
8. **Budget optimisé** : Conception sous les 500 $.

---

## 🔧 Configuration et installation

### Micrologiciel

Le micrologiciel est basé sur LucidGloves et optimisé pour ESP32. Notre version personnalisée est située dans le répertoire `/firmware` du projet.

**Configuration par défaut :**
- Microcontrôleur : ESP32
- Communication : Bluetooth Serial
- Support des retours haptiques avancés

### Méthodes de communication supportées
- Bluetooth Serial (ESP32)
- Wi-Fi (ESP32)
- USB Serial (mode debug)

### Instructions de configuration

1. Ouvrir les fichiers firmware dans le dossier `firmware/lucidgloves-firmware`
2. Configurer les paramètres dans le fichier `lucidgloves-firmware.ino`
3. Modifier les définitions (`#define`) selon votre configuration matérielle

**Guide de configuration détaillé :** [Configuration Instructions](https://github.com/LucidVR/lucidgloves/wiki/Firmware-Setup-and-Customization-Tutorial)

---

## 🖨️ Matériel et impression 3D

### Pièces imprimées 3D requises (par main)

**Guide d'impression :** [Printing guide](https://github.com/LucidVR/lucidgloves/wiki/Parts-Printing-Guides)
**Liste complète des composants :** [Parts Lists](https://github.com/LucidVR/lucidgloves/wiki/Parts-Lists)

### Composants électroniques additionnels

**Composants optionnels pour ce projet :**
- Joysticks pour la locomotion
- Boutons (la plupart peuvent être remplacés par des gestes)
- Modules Peltier pour retour thermique
- Vibreurs tactiles
- Circuit imprimé personnalisé

---

## 🎮 Compatibilité SteamVR (OpenGloves)

Ce projet utilise le driver OpenGloves OpenVR pour la compatibilité avec SteamVR :

**Téléchargement :** https://store.steampowered.com/app/1574050/OpenGloves/
**Code source :** https://github.com/LucidVR/opengloves-driver

---

## 🧪 Tests et validation

- Tests unitaires sur le micrologiciel, la communication et la détection de gestes
- Tests de retour de force (oscilloscope, échelle de Likert utilisateur)
- Tests thermiques (capteurs de température)
- Tests d'intégration VR avec Unity (Carnaval VR)
- Évaluation utilisateur en situation immersive

---

## 📚 Ressources et documentation

### Documentation LucidGloves
- **Wiki officiel :** https://github.com/LucidVR/lucidgloves/wiki
- **Guide de configuration :** [Firmware Setup and Customization Tutorial](https://github.com/LucidVR/lucidgloves/wiki/Firmware-Setup-and-Customization-Tutorial)
- **Dépannage :** [Firmware Troubleshooting Guide](https://github.com/LucidVR/lucidgloves/wiki/Firmware-Troubleshooting-Guide)

### Support communautaire
- **Discord LucidVR :** https://discord.gg/lucidvr
- **TikTok Lucas_VRTech :** https://www.tiktok.com/@lucas_vrtech
- **Site web :** http://lucidvrtech.com/

---

## 📄 Licence et crédits

Ce projet repose sur le travail de la communauté open-source **LucidVR**.  
Nous remercions la communauté pour la base logicielle disponible publiquement.

**Crédits spéciaux :**
- Communauté LucidVR pour le firmware et les modèles 3D de base
- Lucas_VRTech pour le développement original des LucidGloves

**Projet réalisé par des étudiants de l'ÉTS à des fins académiques.**  
Aucune visée commerciale.

---

## 📬 Contact

Pour plus d'informations, vous pouvez contacter l'équipe Gantastique via le club **Conjure ÉTS**.

---
