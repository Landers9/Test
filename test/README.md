#First question
1-Protocol: HTTP, PORT: 8080
2-The folders Bin, Boot, Dev
3-Mysql does not have deal with oracle's sequence
4-You can use sudo to perform any action requiring administrator rights without wanting to become super user. For example to do a software installation



#Second question
1-During the development of a website it is necessary to compare the different facets of the site i.e. the font-end and the back-end in order to locate the responsibilities of the specifications, prototyping the products and get along with the customer on his validation
 
The technologies I would use are html css javascript for smaller sites and for larger ones I would use frames like ruby on rails, laravel, vue js, react js

2- code ()

#third question

1- SELECT def_text
   FROM definition 
   INNER JOIN words ON definition.word_id = words.id;

2- SELECT base_form
   FROM words 
   INNER JOIN translations ON translations.word_id = words.id
   WHERE translate_form IS NULL;

3- 