# Logbog

# Indhold

[16/2 2](#_Toc64376677)

# 5/2

Pænt goddag – klar til samarbejde = ja

Hvad skal vi lave? Projektidé udarbejdes – Alle brainstormer til mandag

# 8/2

Opsamling på projekt – vi fastlægger os på projekt

Rig idé osv. udarbejdes og sendes ind

# 16/2

**Møde:**

- Snak om værktøjer (GitHub issues i stedet for Trello)
- Adam valgt som korrespondent på kontakt til John indtil videre
- Vi kører cc på mailkorrespondance, så Adam ikke skal skrive på messenger

**Mail til John:**

- Hvem er vi
- Vi skal have lavet møde med Josefine – vil du se krav evt. spare inden?

**Spørgsmålsliste udarbejdes til Product Owner**

- Udspringer af krav

**Hvordan finder vi ud af krav?**

- Udarbejd kravspecifikation ud fra det
- Ting skal tilsættes inden næste møde / møde med John

Der arbejdedes i breakout rooms med kravspecifikation

Framework for kravsspecifikation – **skal være færdig inden næste møde som er fredag 19/2**

**Arbejdsstruktur**

Én sætter hele mappestrukturen op i overleaf

Alle punkter der skal laves -\&gt; tidslinje -\&gt; Smide ind i timeline -\&gt; Fastlæg alle møder

Møder 2x pr. uge – 1 med John. Vi kunne have 1 time med John og 30 min. før og efter.

# 19/2

Vejledermøde:

Referat:

- John synes det er et fedt projekt med masere af potentiale.
- Bæredygtighed og mere fokus på fagene.
- Vi kigger på kravene som indtil videre er opstillet
  - Punkt 2-7 er meget ens, og input fra Josefine kræves for enhederne
  - Hvor stor må elektronikken være?
  - Hvor meget må den veje?
  - Har biologi allerede sensorer, som vi blot kan interface med?
    - Lower cost!
- Mere kød på hjemmeside – flere krav til hjemmesiden
  - Noget med hjemmesidens grafik
  - Interface
  - Baggrund for use cases
    - Mac – COCO -læg grafisk billede fast – funktionalitet kommer derefter
  - En form for wireframe af hjemmesiden!
- Sensorkasserne kan beskrives meget:
  - Batteridreven?
  - LED for normalmode vs. Xx
  - Resetknap?
  - Interface?
  - Skal man kunne omprogrammere kassen?
- EMC
  - Bare henvise til EMC direktiver – i design og implementering kan EMC så undersøges
  - Test af 1-2 af de EMC-krav fra direktivet.
- John kan godt lide Simons plan!
  - Elastikplan, så den kan ændres med 1-2 uger, men ser mega godt ud!

# 24/2

Vejledermøde:

Referat:

Funktionelle krav:
- Hellere dække HELE systemet i kravspec - og før/efter analysen konkludere, at det bliver for tidskrævende at implementere (fint argument for afgrænsning)

- Regulering af vandstand/salt:
  - Hvor mange vand input er der (salt, salt+vand, vand)?

- Lys:
  - Spec hvad ALLE kravene er som udgangspunkt!
  - Total effekt, effekt fordelt på bølgelængder (båndbredder), spektralt indhold, steps, præcision
  - Lader til at man kan lave fine specs med RGB hvis båndbredden ikke er for snæver (måske der er en standard løsning?)
  - Hvis det bare er RGB: spørgsmål om intensitet fra kilden (hvad er nok power?)
    - Bed om nogle initielle bud fra product owner (ellers har vi egentlig teten)
    - Vi kunne skrive: "der er for mange TBD'er ved lyskilden til at vi vil gå videre med den ... "
    
- GUI:
  - (m) Hvor ofte lagres der? hvert 15 sekund, hver gang der laves ændring af indstillingerne?
  - (p) er der time limited persistance? Hvor langt tilbage gemmes data?
  - (s) Hvordan gøres kalibreringen via UI?
  - Hvad indeholder drop down menu i user interface sketch?
    - Tilføj evt. flere billeder af alt hvad der sker med interaktion med UI (dropdown menuer, knapper m.m.) - kan yderligere lægges i bilagene. 

- Fysisk user interface:
  - Få neglet alt ned (strømstik, reset, power, ...)
 
- EMC:
  - Systemet skal overholde EMC direktivet ...

Use cases:
  - Der mangler use case diagram
  - Sensorer:
    - Ekstern stykke hardware (sekundær aktør) eller en del af systemet
      - Hvis vi selv tager hånd om det: en del af systemet
      - Hvis vi køber det og interface er speccet: ekstern stykke hardware (interface skal så bare specces)
  - Lav en use case for HVER knap som du kan trykke på som giver en handling eller skal eksekvere kode (både GUI og fysisk)
  - Undtagelser: hvilke fejlmeldinger? Hvordan skal de præsenteres (hvilken logfil)?
  - Prækondition (for at undgå der kommer brugermanual elementer i use casen): "De fysiske forudsætninger for systemet er bringet til opfyldelse j.f. (en evt. kort brugermanual i bilag som fortæller hvordan systemet fysisk skal sættes op)

Optakt til analyse:
- Interface til sensorer skal specces hvis de er eksterne!
- Kom med bud til realistisk opløsning på allerede-lavede sensorer ("custom er for tidskrævende" ... er et fint argument)

# 3/3
Vejledermøde:

Referat:

Use cases:
- Generelt:
  - Kommentar fra John: sålænge der er en use case for hver interaktion (alt hvad der kan trykkes på, tændes og slukkes), er det finno!
  - Undlad dybdegående use cases for processer, der ikke begyndes af en handling (opret i stedet prækondition, se evt. under "Use case: Tænd system" kommentarer
  - Undlad at referere til use cases på tværs af use cases

- Use case: Tænd system
  - Tilføj evt. forudsætning (at init.ini) allerede er eksisterende for at undgå at UC tænd bliver vildt lang.
    - Hermed undgås at man skal beskrive HVORDAN init.ini opstår ved blot at have den på som en prækondition (evt. med specifikation af, hvor den er)

  - MEN: Vi laver det sådan, at det faktisk kræver en handling "Tryk på Tænd" for at køre initialisering (hvis der ikke er en i forvejen). Derfor laves følgende ændring i "UC: Tænd". Se nedenstående:
 
 
 Check init fil  \nUndtagelse: der er ikke init fil(læg use case "initialisering" under undtagelse: der er ikke init fil)
 
  Check indhold af init fil
 Undtagelse: indholdet af init fil er garbage
 (slet garbage init fil, kør "initialisering")
 
- Use case: Initialisering
  - Ryk "Use case: Initialisering" op til tænd, da den specifikke handling der begynder "initialisering" ER "UC: Tænd"

- Use case: Reguler
  - Et eller andet sted er der en handling som påbegynder "Reguler"
    - Tændknap på fysisk interface hvis default (fabriksindstillede setpoints) eller igennem startknap på GUI
