(* Ceci est un éditeur pour OCaml
   Entrez votre programme ici, et envoyez-le au toplevel en utilisant le
   bouton "Évaluer le code" ci-dessous. *)

module type GENOME = 
sig
  type individu
  type parametre
  val creer: parametre -> individu
  val muter: individu -> individu
  val croiser: individu -> individu -> individu
end

module MotGenetique : GENOME with type individu = string and type parametre = int = 
struct
  type individu = string
  type parametre = int
    
  let creer = fun parametre ->
    let rand_chr () = char_of_int (97 + (Random.int 26)) in
    let rec boucle l parametre = 
      if parametre == 0 then l else boucle (l ^(String.make 1 (rand_chr()))) (parametre-1) in
    boucle (String.make 1 (rand_chr())) (parametre-1)
  

  let rec muter = fun l ->
    let longueur = String.length l in let
      rand_chr () = char_of_int (97 + (Random.int 26)) in 
    if l="" then ""
    else if Random.int 100 > 5 then 
      let l' = String.make 1 l.[0] in 
      l'^ muter (String.sub l (1) (longueur-1))
    else 
      let l' = String.make 1 (rand_chr()) in
      l'^ muter (String.sub l (1) (longueur-1))

  let croiser = fun mot1 mot2 ->
    let lg = String.length mot1 in
    if lg = String.length mot2 then let n = (Random.int (lg) ) in 
      (String.sub mot1 0 n )^(String.sub mot2 n (lg-n))
    else mot2
end

module type EvolutionType = functor (Mot: GENOME) ->
sig 
  type population = Mot.individu list
  type evaluateur = Mot.individu -> int
  val reproduction : population -> int -> population
  val mutation : population -> population
  val selection : evaluateur -> population -> int -> population
  val generation : evaluateur -> int -> int -> population -> population
  val evolution : evaluateur -> Mot.parametre -> int -> int ->int -> population
end
module Evolution : EvolutionType = functor (Mot:GENOME) ->
struct 
  type population = Mot.individu list
  type evaluateur = Mot.individu -> int
  let rec reproduction l n =
    let taille = List.length l in
    if l == [] then l
    else
    if n == 0 then l
    else
      let x = List.nth l (Random.int(taille-1)) in
      let y = List.nth l (Random.int(taille-1)) in
      let enfant = Mot.croiser x y in
      reproduction (l@[enfant]) (n-1)
  let mutation liste=
    let rec muterliste liste liste2 indice= 
      if indice == List.length liste then snd (List.split liste2)
      else muterliste liste (liste2@[(Mot.muter (List.nth liste indice),List.nth liste indice)]) (indice+1) in
    muterliste liste [] 0
  let selection = fun evaluateur pop nbrsurvivant ->
    let appliquerliste liste evaluateur=
      let rec creerlisteappliquer liste liste2 indice= 
        if indice == List.length liste then liste2
        else creerlisteappliquer liste (liste2@[(evaluateur (List.nth liste indice),List.nth liste indice)]) (indice+1) in
      creerlisteappliquer liste [] 0 in
    let rec couperliste valeur liste = match liste with
      | [] -> failwith "liste vide couperliste"
      | y::liste -> if valeur=1 then [y] else y::couperliste (valeur-1) liste in
    snd (List.split (couperliste nbrsurvivant (List.sort compare (appliquerliste pop evaluateur))))
  let generation = fun evaluateur nbrvivant nbrsurvivant pop ->
    mutation (reproduction ( selection evaluateur pop nbrsurvivant ) nbrvivant)
  let evolution = fun evaluateur parametre nb_individus nb_meilleurs max_iter ->
    let rec creerpop parametre nb_individus pop= if nb_individus ==0 then pop
      else creerpop parametre (nb_individus-1) (pop@[Mot.creer parametre]) in
    let rec evoluer evaluateur nb_individus nb_meilleurs max_iter popfinal =
      if max_iter == 0 then popfinal
      else evoluer evaluateur nb_individus nb_meilleurs (max_iter-1) (generation evaluateur nb_individus nb_meilleurs popfinal)in
    evoluer evaluateur nb_individus nb_meilleurs max_iter (creerpop parametre nb_individus [])
end 
;;

module Mystere = Evolution(MotGenetique) ;;

let comparer = fun mot1 -> fun mot2 ->
  if String.length mot1 != String.length mot2 then
    failwith "les gênes ne font pas la même taille"
  else let rec enumerer x y z =
         if x = "" then
           z
         else
         if String.sub x 0 1 = String.sub y 0 1 then 
           enumerer (String.sub x 1 ((String.length x)-1)) (String.sub y 1 ((String.length y)-1)) z else
           enumerer (String.sub x 1 ((String.length x)-1)) (String.sub y 1 ((String.length y)-1)) z+1
    in enumerer mot1 mot2 0 ;;