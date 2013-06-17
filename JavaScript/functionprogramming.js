function buildPerson(name, target) {            
    return {
        speak: function(where) {
            if ( !where ) where = target;
             
            var words = 'Hello, my name is <span class="answer">{0}</span><br>';
            where.append( supplant(words, [name]) );                         
        }
    };
}

// old solution
var names  = ['Thomas Burleson', 'John Yanarella', 'Indiver Nagpal'],
     
for (var i = 0, len = names.length; i < len; i++) {
    buildPerson(names[i]).speak()
}    

// functional solution
var names  = ['Talon', 'Forest', 'Kim'];
 
_.each( 
      _.map( 
          names, 
          function (name) { 
           return buildPerson(name); 
          }
      ),
     function( cat ) {
         cat.speak();
     }
 );

// better functional solution
var names  = ['Adam', 'Ben', 'Grant'];
 
 _.chain(names)
  .map( function (name) {
    return buildPerson(name);
  })
  .each( function (person) {
    person.speak();
  });
