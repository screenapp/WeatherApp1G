const express = require('express');
const app = express();
const bodyParser = require('body-parser');
app.use(bodyParser.json());
const port = 3005;

app.listen(port, () => console.log(`screen-app listening on port ${port}!`));

const Sequelize = require('sequelize');
const sequelize = new Sequelize({
  dialect: 'sqlite',
  storage: './database.sqlite'
});

sequelize.authenticate()
  .then(() => {
    console.log('Connection has been established successfully.');
  })
  .catch(err => {
    console.error('Unable to connect to the database:', err);
  });

  const Profile = sequelize.define('profiles', {
    username: {
      type: Sequelize.DataTypes.STRING,
      allowNull: false,
      unique: true,
      validate: {
        isAlphanumeric: true,
        max: 24,
        notNull: true
      }
    },
    password: {
      type: Sequelize.DataTypes.STRING,
      allowNull: false,
      validate: {
        isAlphanumeric: true,
        max: 24,
        notNull: true
      }
    },
    location: {
      type: Sequelize.DataTypes.STRING,
      allowNull: false,
      validate: {
        isAlphanumeric: true,
        max: 85,
        notNull: true
      }
    },
    newstag: {
      type: Sequelize.DataTypes.STRING,
      allowNull: false,
      validate: {
        isAlphanumeric: true,
        notIn: [[' ']],
        max: 85,
        notNull: true
      }
    },
    active: {
      type: Sequelize.DataTypes.BOOLEAN
    }
    });

sequelize.sync({ force: true })
  .then(() => {
    console.log(`Database & tables created!`);

    Profile.bulkCreate([
      { username: 'user1', password: 'screenappuser1', location: 'ottawa', newstag: 'ottawa', active: false },
      { username: 'user2', password: 'screenappuser2', location: 'ottawa', newstag: 'sports', active: false },
      { username: 'user3', password: 'screenappuser3', location: 'miami', newstag: 'miami', active: true }
    ]).then(function() {
      return Profile.findAll();
    }).then(function(profiles) {
      console.log(profiles);
    });
  });

// Routes
app.get('/', (req, res) => res.send('Screen App'));

app.get('/profiles', function(req, res) {
  Profile.findAll().then(profiles => res.json(profiles));
});

// app.get('/notes/search', function(req, res) {
//   Note.findAll({ where: { note: req.query.note, tag: req.query.tag } }).then(notes => res.json(notes));
// });

const Op = Sequelize.Op;

app.get('/profiles/search', function(req, res) {
  Profile.findAll({
    limit: 1,
    where: {
      active: {
        [Op.or]: [].concat(req.query.active)
      }
    }
  }).then(notes => res.json(notes));
});

app.get('/profiles/:id', function(req, res) {
  Profile.findAll({ where: { id: req.params.id } }).then(profiles => res.json(profiles));
});

app.post('/profiles', function(req, res) {
  Profile.create({ username: req.body.username, password: req.body.password, location: req.body.location, newstag: req.body.newstag, active: req.body.active }).then(function(profile) {
    res.json(profile);
  });
});

app.put('/profiles/:id', function(req, res) {
  Profile.findByPk(req.params.id).then(function(profile) {
    profile.update({
      username: req.body.username,
      password: req.body.password,
      location: req.body.location,
      newstag: req.body.newstag,
      active: req.body.active
    }).then((profile) => {
      res.json(profile);
    });
  });
});

app.delete('/profiles/:id', function(req, res) {
  Profile.findByPk(req.params.id).then(function(profile) {
    profile.destroy();
  }).then((profile) => {
    res.sendStatus(200);
  });
});