# IA_Devoir_2
 
Evan Weisse : WEIE05079905
Jorick Célarier : CELJ29089807

Pour ce TP, nous avons réalisé les 2 classes Leader et Follower au sein d'un même fichier Agent.
La classe Leader s'occupe donc de gérer le comportement du leader, celle-ci est assez simple car le leader ne fait que errer sur la carte.
La classe Follower s'occupe de gérer le comportement des poursuiveurs. Leur comportement de base est également d'errer, mais dès qu'ils sont assez proche de la queue de la file des poursuiveurs, alors ils s'ajoutent en bout de queue (ceci étant fait grâce à une boucle sur tous les agents qui n'ont pas encore de suiveur ...).

De plus, le début des comportements avec un contrôleur humain a été implémenté. Avec la touche H, le comportement des followers et du leader devraient être affectés, cependant nous avons fait face à des problèmes que nous n'avons pas su régler. D'un côté, le déplacement du leader avec les flèches directionnelles n'est pas concluant : les actions sont prises en compte, mais cela ne permet pas au leader d'effectuer un déplacement concluant. De l'autre côté, même si nous changeons le comportement des followers pour désormais suivre le leader, ceux ci ne changent pas de comportement et continue de poursuivre l'agent devant eux dans la file.