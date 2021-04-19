# Planlægning

## Projekt faser

| Faser             | Start      | Slut       |
|-------------------|------------|------------|
| Projektdefinering | 2021/02/01 | 2021/02/12 |
| Krav              | 2021/02/15 | 2021/02/26 |
| Strukturering     | 2021/03/01 | 2021/03/12 |
| Analyse           | 2021/03/15 | 2021/03/26 |
| Design            | 2021/03/05 | 2021/04/16 |
| Implementering    | 2021/04/19 | 2021/05/07 |
| Rapport           | 2021/05/10 | 2021/05/25 |

![Tidsplanen](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/Solvgraa-mager/E4PRJ4/main/Planing/timeline.puml)

## Møder

### Krav 1
##### Dato: 17/02/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder:
###### Referent:

###### Agenda: 


##### Action Item Liste: 

- [ ] Opsætning af LaTeX (Adam)
- [ ] Formulering af ikke-funktionelle krav (Alle)

---
### Krav 2
##### Dato: 24/02/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: 
###### Referent: 

##### Agenda:
1. Gennemgang af krav (sidste rettelser inden input) 
   1. Husk lys!
3. Arrangere møde med Josefine 
4. Gennemgang af AI fra sidst:
   1. Størrelse og vægt på systemet (Villiam) 
   2. Sensorer (Adam)  
   3. Sketch af webpage (Simon)
   4. Sketch af systemet (Villiam) 
   5. EMC tilføjet til kravliste (?) 
6. Use Cases!  

##### Action Item Liste: 
- [ ] Test cases udarbejdes

---
### Strukturering 1
##### Dato: 03/03/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: Christian
###### Referent: 

##### Agenda:
1. Kravfasen gennemgås og lukkes. Eventuelle spørgsmål til use cases stilles.
2. Hvordan gør vi strukturering? 
3. Opdeling af systemet i moduler
   1. Overskrifter: Delmoduler
   2. Sketch af forbindelser mellem delmoduler
4. Uddelegering af moduler

  
##### Action Item Liste: 
- [ ] Systemet IBD fra sketch til flot
- [ ] Detaljeret spec af forbindelser 
- [ ] IBD af delmoduler med interne forbindelser og fuld spec

---
### Strukturering 2
##### Dato: 10/03/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: 
###### Referent: 

##### Agenda:
1. Grupper viser deres delmoduler og gruppen kommer med kommentarer
  
##### Action Item Liste: 
- [ ] IBDer og forbindelser rettes jf. kommentarer

---
### Strukturering 3
##### Dato: 17/03/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: 
###### Referent: 

##### Agenda:
1. Hvordan gør vi analyse? 

2. Team SE: 
   1.  Team SE: Kategorisering af krav for alle blokke? 
   2.  Hjælp til spec af DC2 9V strømforsyning
   3.  Hjælp til spec af SensorCom SPI forbindelse ift. en lang ledning og noget med impedans.. 

3. Team CC og samlet system:
   1. Skal der være blok/signal til samlet system BDD og IBD? Eller er det fint, at disse udspecificeres under respektive afsnit?
   2. Gennemgang af sekvensdiagram for samlet system
   3. Er det så i analysen vi finder ud af, om hjemmeside køres med websocket el. lign?

4. Team AE:
   1. Specifikation af reguleringsparametre (overshoot, risetime ... ) - i blokbeskrivelse (og i det tilfælde - for signalet eller "outputtet" = væske, varme osv)?
   2. Afklaring omkring krav for pumper (flow rate m.m.) - har skrevet til regulerings Martin omkring modellering af DC pumper
   3. Strategi for formulering af afgrænsning. 
  
##### Action Item Liste: 
- [ ] Analyseafsnit for delmoduler udarbejdes 

---
### Analyse 1
##### Dato: 24/03/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: 
###### Referent: 

##### Agenda:
1. Hvordan gør vi analyse? 
   1. Afstemning af hvad analyse-afsnittet indebærer

2. Team AE:
   1. Ny strukturering af lys enhed gennemgås
   2. output karakteristikker for outputs 
   
  
##### Action Item Liste: 
- [ ] Analyseafsnit tilrettes jf. kommentarer


---
### Analyse 3
##### Dato: 07/04/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: Christian
###### Referent: David

##### Agenda:
1. Valg af ny mødeleder
2. Hvordan gør vi design? 
3. Spørgsmål fra CC ang: 
   1. Controlboard
   2. Embedded Controller
   3. Hjemmeside

Team AE:
1. Skillelinje mellem analyse og design ifht. f.eks. valg af transistorer for driver kredsløb


---
### Design 1
##### Dato: 14/04/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: Adam
###### Referent: 

##### Agenda:
1. Nye ting i analyseafsnit gennemgås + De designafsnit der måtte være færdige vises
2. Eksakt afleveringsdato? (Simon har ledt overalt på BB uden held)
3. Hvordan håndterer vi referencer?
4. SE: Valid begrundelse for hastighed og bit på MCU'ens processor? 
5. SE: 4-20mA forsyning - erfaringer?

---
### Design 2
##### Dato: 21/04/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: 
###### Referent: 

##### Agenda:
  1. Designafsnit gennemgås
  1.2CC:
      1. præs af NY domænemodel
      2. Groft forklaring af fremgangsmåde fra UseCases -> domæne -> koncep. klasse osv...
      3. Problematikken ved UseCases kontra CentralComputer - <<controller>>
      4. Problematikken ved to forskellige software arkitekturer - CC og hjemmesiden
  3. Simon: FunctionDescription flyver lidt rundt - er der stemning for at overskrive Latex-float på dem? (Behøver ikke komme på agenda til John :-))
  
---
### Implementering 1
##### Dato: 28/04/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: 
###### Referent: 

##### Agenda:
  1. Implementeringsafsnit fremvises og gruppen kommer med kommentarer

---
### Implementering 2
##### Dato: 05/05/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: 
###### Referent: 

##### Agenda:
  1. Hvordan gør vi test? 
  2. Hvem laver integrationstest? 

---
### Test 1
##### Dato: 12/05/2021
##### Tidspunkt: 10:00 - 12:00
###### Mødeleder: 
###### Referent: 

##### Agenda:
  1. Testafsnit fremvises og gruppen kommer med kommentarer 
  

