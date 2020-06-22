# thanos_docker_and_plugin
Docker setup with prometheus, grafana, node-exporter and thanos. Includes c++ based plugin to fetch from thanos API and script to install required libraries

To run this project, first clone this repository - 
> git clone https://github.com/the-yash/thanos_docker_and_plugin.

After having cloned the repository, to set up the libraries required for the plugin
``` 
chmod u+x env_setup.sh
./env_setup.sh 
```

Start the docker containers to see the metrics graphically
> docker-compose up -d

To compile the plugin
> make

To run the plugin
>./combine

The plugin will run send the request and fetch the json after every second unless you decide to terminate it.

To stop the execution, press Ctrl+C to terminate it.

To see the Grafana dashboard, open your browser and type http://localhost:3000. Credentials are the default ones.

To run the queries for metrics from Thanos (Prometheus based), open your browser and type http://localhost:10904.

To run see the objects stored, open your browser and type http://localhost:9000. Credentials are mentioned in the data/bucket.yml file.

To stop the containers,
> docker-compose down
