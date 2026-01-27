rm -rf /tmp/* > /dev/null 2>&1;
cd ..;
env -i /bin/bash -c '(source testing-env.sh; env >test.env)';
mv test.env /tmp/test.env;
tar xzf sandbox.tgz;
mv sandbox /tmp;
